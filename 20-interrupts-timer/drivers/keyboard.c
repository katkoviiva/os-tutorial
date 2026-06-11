#include "keyboard.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "../kernel/util.h" // Assuming this is where int_to_ascii is defined
#include "screen.h"

void print_letter(u8 scancode); // Add this prototype!

static void keyboard_callback(registers_t regs) {
    u8 scancode = port_byte_in(0x60);
    
    // Create a buffer large enough for a 3-digit number and null terminator
    char sc_ascii[4]; 
    int_to_ascii(scancode, sc_ascii);
    
    kprint("Keyboard scancode: ");
    kprint(sc_ascii);
    kprint(", ");
    print_letter(scancode);
    kprint("\n");
}

void init_keyboard() {
   register_interrupt_handler(IRQ1, keyboard_callback); 
}

// Define a lookup table for the main keys
const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "+", "Backspace", "Tab", "Q", "W", "E", 
    "R", "T", "Y", "U", "I", "O", "P", "[", "]", "ENTER", "LCtrl", 
    "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
    "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
    "/", "RShift", "Keypad *", "LAlt", "Spc"};

void print_letter(u8 scancode) {
    if (scancode <= 0x39) {
        kprint(sc_name[scancode]);
    } else {
        if (scancode <= 0x7f) {
            kprint("Unknown key down");
        } else if (scancode <= 0x39 + 0x80) {
            kprint("key up ");
            // Recursive call is safe here because (scancode - 0x80) 
            // will be <= 0x39
            print_letter(scancode - 0x80); 
        } else {
            kprint("Unknown key up");
        }
    }
}

