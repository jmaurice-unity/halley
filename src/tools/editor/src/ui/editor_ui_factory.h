#pragma once
#include "halley/ui/ui_factory.h"

namespace Halley {
    class EditorUIFactory : public UIFactory {
    public:
		EditorUIFactory(const HalleyAPI& api, Resources& resources, I18N& i18n);
    };
}
