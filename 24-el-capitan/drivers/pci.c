#include "pci.h"
#include "../cpu/ports.h"      // Contains the declarations for outl/inl
#include "../drivers/screen.h" // Contains the declaration for kprint
#include "../libc/string.h"

uint16_t pciConfigReadWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
    uint32_t address = (uint32_t)((bus << 16) | (slot << 11) | (func << 8) | (offset & 0xFC) | 0x80000000);
    outl(0xCF8, address);
    return (uint16_t)((inl(0xCFC) >> ((offset & 2) * 8)) & 0xFFFF);
}

void check_all_pci_buses() {
    for (uint16_t bus = 0; bus < 256; bus++) {
        for (uint8_t slot = 0; slot < 32; slot++) {
            uint16_t vendor = pciConfigReadWord(bus, slot, 0, 0x00);
            if (vendor != 0xFFFF) {
				// Inside check_all_pci_buses()
				char buffer[16]; // Buffer to hold the converted string
				kprint("Found PCI Device at Bus: ");
				int_to_ascii(bus, buffer); // 1. Convert number to string in 'buffer'
				kprint(buffer);            // 2. Print the now-populated 'buffer'
				kprint(" Slot: ");
				int_to_ascii(slot, buffer);
				kprint(buffer);
				kprint("\n");
            }
        }
    }
}