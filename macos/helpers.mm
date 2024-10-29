
// MacOSHelper.mm
#include <Cocoa/Cocoa.h>

void setAquaAppearance() {
    if (__builtin_available(macOS 10.14, *)) {
        [NSApp setAppearance:[NSAppearance appearanceNamed:NSAppearanceNameAqua]];
    }
}
