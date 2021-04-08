ENTRY(_kmain)

SECTIONS {
  . = 0x10000;
  .kernel :
  {
    *(.text*)
    *(.rodata*)
    *(.rdata*)
    *(.data)
    _bss_start = .;
    *(.bss)
    *(COMMON)
    _bss_end = .;
  }
  /DISCARD/ : {
        *(.eh_frame)
        *(.comment)
  }
}