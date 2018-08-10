#pragma once

#include "halley/core/input/input_keyboard.h"
#include <winrt/Windows.UI.Text.Core.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.System.h>
#include <set>

namespace Halley {
	class WinRTTextInputCapture;

	class WinRTKeyboard : public InputKeyboard {
	public:
		WinRTKeyboard();
		~WinRTKeyboard();
		void update();
		
		void addCapture(WinRTTextInputCapture* capture);
		void removeCapture(WinRTTextInputCapture* capture);

	protected:
		Maybe<winrt::Windows::UI::Core::CoreWindow> window;
		winrt::event_token acceleratorKeyEvent;

		std::vector<int> keyMapping;
		std::set<WinRTTextInputCapture*> captures;

		void initMapping();
		std::unique_ptr<ITextInputCapture> makeTextInputCapture() override;
		Maybe<int> getHalleyKey(winrt::Windows::System::VirtualKey virtualKey);
		void onTextControlCharacterGenerated(TextControlCharacter chr);
	};

	class WinRTTextInputCapture : public ITextInputCapture {
	public:
		WinRTTextInputCapture(WinRTKeyboard& parent);
		~WinRTTextInputCapture();

		void open(TextInputData& input, SoftwareKeyboardData softKeyboardData) override;
		void close() override;
		bool isOpen() const override;
		void update() override;
		void onControlCharacter(TextControlCharacter chr);

	private:
		WinRTKeyboard & parent;
		TextInputData* input = nullptr;
		Maybe<winrt::Windows::UI::Text::Core::CoreTextServicesManager> servicesManager;
		Maybe<winrt::Windows::UI::Text::Core::CoreTextEditContext> editContext;
	};	
}
