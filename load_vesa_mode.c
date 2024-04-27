//TEST VESA VIDEO MODES with BORLAND Turbo C++ 3.0
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <dos.h>


void carga_total(char *fichero);
void loadVesaModes();
unsigned char *vga = (unsigned char *) MK_FP(0xA000,0);

FILE *archivo;
void main(){

   cout << "DEMO LOAD VESA MODES\n";
   cout << "Press a key to load the video mode\n";
   getch();
   loadVesaModes();
   getch();
}

// VESA VIDEO MODES : https://fd.lod.bz/rbil/interrup/video/104f02.html
void loadVesaModes(){

    //Elijo tipo de resolucion en modo VESA
	asm{
	  mov ax,4F02h
      mov bx,107h
      int 10h
	}
	printf("HELLO WORLD");
}

/*
(Table 00083)
Values for VESA video mode:
 00h-FFh OEM video modes (see #00010 at AH=00h)
 100h	640x400x256
 101h	640x480x256
 102h	800x600x16
 103h	800x600x256
 104h	1024x768x16
 105h	1024x768x256
 106h	1280x1024x16
 107h	1280x1024x256
 108h	80x60 text
 109h	132x25 text
 10Ah	132x43 text
 10Bh	132x50 text
 10Ch	132x60 text
---VBE v1.2+ ---
 10Dh	320x200x32K
 10Eh	320x200x64K
 10Fh	320x200x16M
 110h	640x480x32K
 111h	640x480x64K
 112h	640x480x16M
 113h	800x600x32K
 114h	800x600x64K
 115h	800x600x16M
 116h	1024x768x32K
 117h	1024x768x64K
 118h	1024x768x16M
 119h	1280x1024x32K (1:5:5:5)
 11Ah	1280x1024x64K (5:6:5)
 11Bh	1280x1024x16M
---VBE 2.0+ ---
 120h	1600x1200x256
 121h	1600x1200x32K
 122h	1600x1200x64K
81FFh	special full-memory access mode
Notes:	the special mode 81FFh preserves the contents of the video memory and
	  gives access to all of the memory; VESA recommends that the special
	  mode be a packed-pixel mode.	For VBE 2.0+, it is required that the
	  VBE implement the mode, but not place it in the list of available
	  modes (mode information for this mode can be queried directly,
	  however).
	as of VBE 2.0, VESA will no longer define video mode numbers
SeeAlso: #00010,#00011,#00084,#00191
Index:	video modes;VESA


(Table 00084)
Values for S3 OEM video mode:
 201h	640x480x256
 202h	800x600x16
 203h	800x600x256
 204h	1024x768x16
 205h	1024x768x256
 206h	1280x960x16
 207h	1152x864x256 (Diamond Stealth 64)
 208h	1280x1024x16
 209h	1152x864x32K
 20Ah	1152x864x64K (Diamond Stealth 64)
 20Bh	1152x864x4G
 211h	640x480x64K (Diamond Stealth 24)
 211h	640x400x4G  (Diamond Stealth64 Video / Stealth64 Graphics)
 212h	640x480x16M (Diamond Stealth 24)
 301h	640x480x32K
Note:	these modes are only available on video cards using S3's VESA driver
SeeAlso: #00083,#00191,#00732 at INT 1A/AX=B102h
Index:	video modes;S3


Format of VESA VBE CRTC Information Block:
Offset	Size	Description	(Table 04083)
 00h	WORD	total number of pixels horizontally
 02h	WORD	horizontal sync start (in pixels)
 04h	WORD	horizontal sync end (in pixels)
 06h	WORD	total number of scan lines
 08h	WORD	vertical sync start (in scan lines)
 0Ah	WORD	vertical sync end (in scan lines)
 0Ch	BYTE	flags (see #04084)
 0Dh	DWORD	pixel clock, in Hz
 11h	WORD	refresh rate, in 0.01 Hz units
		this field MUST be set to pixel_clock / (HTotal * VTotal),
		  even though it may not actually be used by the VBE
		  implementation
 13h 40 BYTEs	reserved


Bitfields for VESA VBE CRTC Information Block flags:
Bit(s)	Description	(Table 04084)
 0	enable double scanning
 1	enable interlacing
 2	horizontal sync polarity (0 positive, 1 negative)
 3	vertical sync polarity (0 positive, 1 negative)
SeeAlso: #04083*/