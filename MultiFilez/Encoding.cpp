#include "stdafx.h"
#include "encoding.h"

void encodeBase64(char *out, char *in)
{
	char tob64[] = 
   		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	int linelen;
	int i, l, j, k;
  unsigned long triple;
  unsigned char inb;

  linelen = (strlen(in) - 1); 

  i = 0;j = 0;k = 0;
  triple = 0;
  while (j <= linelen) {
    i++;
    inb = (unsigned char)in[j];
    triple = (triple <<8) | inb;
    if (i == 3 || j == linelen) {
	  	switch (i) {
	    	case 1:
	      		triple = triple<<4;
	      		break;
	    	case 2:
	      		triple = triple<<2;
	      		break;
	    	default:
	      		break;
	    }
	  	for (l = i; l >= 0; l--) {
		    int rr;
		    rr = 0x3f & (triple>>(6*l));
	      	out[k] = tob64[rr];
  			k++;
	    }
	  	if (j == linelen)
	    	switch(i)	{
	      	case 2:
		  		strcat_s(out, strlen(out) + 2, "=");
  					break;
	      	case 1:
    				strcat_s(out, strlen(out) + 3, "==");
		  			break;
	    		default:
			  		break;
	      }
	  		triple = 0;
	  		i = 0;
	  }
	j++;
  }
}
void decodeBase64(char *out, char *in)
{
	int fromb64[] = {
		FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL,  
		FAIL, SKIP, SKIP, FAIL, FAIL, SKIP, FAIL, FAIL,
		FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL,  
		FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL,  
		
		SKIP, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL,
		FAIL, FAIL, FAIL, 0x3e, FAIL, FAIL, FAIL, 0x3f,
		0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b,  
		0x3c, 0x3d, FAIL, FAIL, FAIL, SKIP, FAIL, FAIL,

		FAIL, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,  
		0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e,
		0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,  
		0x17, 0x18, 0x19, FAIL, FAIL, FAIL, FAIL, FAIL,
		
		FAIL, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20,  
		0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
		0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30,  
		0x31, 0x32, 0x33, FAIL, FAIL, FAIL, FAIL, FAIL,
		
		FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL,  
		FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL,
		FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL,  
		FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL,
		FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL,  
		FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL,
		FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL,  
		FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL,
		FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL,  
		FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL,
		FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL,  
		FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL,
		FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL,  
		FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL,
		FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL,  
		FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL, FAIL
		};

	int linelen;
	int i, l, j, k;
  unsigned long triple;
  int inb;

  linelen = (strlen(in) - 1); 

  i = 0;j = 0;k = 0;
  triple = 0;
  while (j <= linelen){
   	inb = fromb64[(unsigned char)in[j]];
		switch(inb) {
			case FAIL:
				break;
			case SKIP:
				break;
			default:
				i++;
				triple = triple<<6 | (0x3f & inb);
       	break;
		}
    if (i == 4 || j == linelen)	{
	  	switch (i) {
	    	case 2:
	      	triple = triple>>4;
	      	break;
	    	case 3:
	      	triple = triple>>2;
	      	break;
	    	default:
	      	break;
	    }
			for (l = i-2; l >= 0; l--) {
  			out[k] = (unsigned char)(0xff & (triple>>(l*8)));
				k++;
    	}
	  	triple = 0;
	  	i = 0;
	 	}
	j++;
  }
}

