%added this code to linker

MEMORY
{
...

	OPEN_AMP_RSC_TAB (xrw)	: ORIGIN = 0x38000000, LENGTH = 1K
	OPEN_AMP_SHMEM (xrw) : ORIGIN = 0x38000400, LENGTH = 63K
}

__OPENAMP_region_start__ = ORIGIN(OPEN_AMP_SHMEM);
__OPENAMP_region_end__ = ORIGIN(OPEN_AMP_SHMEM) + LENGTH(OPEN_AMP_SHMEM);


  .openamp_section (NOLOAD) : 
  {
    . = ABSOLUTE(0x38000000);
    *(.resource_table)
  } > OPEN_AMP_RSC_TAB AT >FLASH
