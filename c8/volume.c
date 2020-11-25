/* Plays a frequency on PD5 with a trigger for an RC circuit on PD0 */

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>

#include "et_scale.h"

/* Inaudible frequencies used to indicate state for melody2freq: */
#define M2F_END    0
#define M2F_REST   1
#define M2F_UNKOWN 2

const char melody[] ="\
X:1\n\
T: Prelude from first Cello Suite\n\
C: J.S. Bach, here transposed for mandolin\n\
M: 4/4\n\
L: 1/16\n\
K:D\n\
(DAf)e fAfA (DAf)e fAfA | (DBg)f gBgB (DBg)f gBgB |\n\
(Dcg)f gcgc (Dcg)f gcgc | (Ddf)d fdfd (Ddf)d fdfd |\n\
(DBf)e fdcd Bdcd FA^GF  | (^Gde)d eded (^Gde)d eded |\n\
(cea)^g aede cede AcBA  | (B,Fd)c dFdF (B,Fd)c dFdF |\n\
(B,^GA)B AGFE (dcB)a ^gfed | (cBA)a eace (ABc)e dcBA |\n\
^d(A=cB) cAdA f(AcB) cAdA  | (GBe)f geBA (GBe)f ge^cB |\n\
^A(cAc) ecec A(cAc) ecec   | (dcB)d cdec dcBA GFED |\n\
CGAG AGAG CGAG AGAG | (DF=c)B cFcF (DFc)B cFcF |\n\
(DGB)A BGBG (DGB)A BGBG | (D^cg)f gcgc (Dcg)f gcgc |\n\
(DAf)e fdcB AGFE DCB,A, | ^G,(EBc) dBcd G,(EBc) dBcd |\n\
=G,(EAB) cABc =G,(EAB) cABc | G,(EAc) (e^g(a2) a)EF=G ABcd |\n\
%second part\n\
(ecA)B cdef (gec)d efga | _ba^ga a=gfg gec=B AEFG |\n\
A,(EAc) efge (fdA)G FDEF | A,DFA defe ^g=fef fe^de |\n\
e=dcd dB^GF EGBd e^gag | aecB ceAc EA^GF EDCB, |\n\
A,2 (=gf edcB A)(gfe dcBA | G)(fed cBAG F)(edc BAGF |\n\
F)(dcB) [cc]e[AA]e [BB]e[cc]e [dd]e[BB]e | [cc]e[AA]e [dd]e[BB]e [cc]e[AA]e [dd]e[BB]e |\n\
[cc]e[AA]e [BB]e[cc]e [dd]e[ee]e [ff]e[AA]e | [ee]e[ff]e [gg]e[AA]e [ff]e[gg]e [aa]e[ff]e |\n\
[gg]e[ff]e [gg]e[ee]e [ff]e[ee]e [ff]e[dd]e | [ee]e[dd]e [ee]e[cc]e [dd]e[cc]e [dd]e[BB]e |\n\
ceAB =cA^cA dA^dA eA=fA | ^fAgA ^gAaA ^bA=bA=c'A^c'A |\n\
d'(fAf) d'fd'f d'(fAf) d'fd'f | d'(eAe) d'ed'e d'(eAe) d'ed'e |\n\
c'(gAg) c'gc'g c'(gAg) c'gc'g | [D16Afd'] |]\
";

unsigned long tone_clock;

#define TONE_PRESCALER 8UL

void init_tone(void);
void init_pwm(void);
void tone(uint16_t frequency);
void volume(uint8_t x);
uint16_t melody2freq(const char *abc_melody);

#define TRIGGER_LENGTH 25
#define STEP_DELAY_MS 450

int main() {
    uint16_t f;

    DDRB |= _BV(PB7); /* LED */
	DDRD |= _BV(0); /* Trigger */

	PORTD = 0;
    init_tone();
	init_pwm();
    
    for(;;){
    	melody2freq(melody);  /* initialise  */
    	while((f=melody2freq(NULL)) != M2F_END) {
    		if (f == M2F_UNKOWN) continue; /* skip unknown symbols */
			volume(OCR2A + 10);
    		tone(f);
			PORTD |= _BV(0);
			_delay_ms(TRIGGER_LENGTH);
			PORTD &= ~_BV(0);
    		_delay_ms(STEP_DELAY_MS - TRIGGER_LENGTH);
		PORTB ^= _BV(PB7); /* toggle LED */
    	}
    	_delay_ms(STEP_DELAY_MS);
    	_delay_ms(STEP_DELAY_MS);
    }
}

void init_pwm(void)
{
    DDRD |= _BV(PD7);
	DDRD |= _BV(PD6);
    TCCR2A = _BV(COM2A1) | _BV(WGM21) | _BV(WGM20);
    TCCR2B = _BV(CS20);
}

void init_tone(void)
{
    DDRD |= _BV(PD5);
    TCCR1A = _BV(COM1A0) | _BV(WGM10);
    TCCR1B = _BV(WGM13) | _BV(CS11);
	TCCR1C = 0;
    tone_clock = F_CPU / (TONE_PRESCALER * 2);
}

void volume(uint8_t x)
{
	OCR2A = x;
}

void tone(uint16_t frequency)
{
    uint16_t top_val = tone_clock / (frequency * 2);
    OCR1A = top_val;
}

uint16_t melody2freq(const char *m) {
    static const char *melody;
    static uint16_t pos;
    static uint8_t scale_index;

    if(m != NULL){  /* initialization */
        melody = m;
        pos = 0;
        return M2F_END; /* to be ignored */
    }

    if(melody[++pos] == '\0') return M2F_END;


    switch( melody[pos] ) {
	case 'c':
	case 'C': {
	    scale_index = ET_SCALE_C;
	    break;
	}
	case 'd':
	case 'D': {
	    /* 2 semitones above C */
	    scale_index = ET_SCALE_C + 2;
	    break;
	}
	case 'e':
	case 'E': {
	    /* 4 semitones above C */
	    scale_index = ET_SCALE_C + 4;
	    break;
	}
	case 'f':
	case 'F': {
	    /* 5 semitones above C */
	    scale_index = ET_SCALE_C + 5;
	    break;
	}
	case 'g':
	case 'G': {
	    /* 7 semitones above C */
	    scale_index = ET_SCALE_C + 7;
	    break;
	}
	case 'a':
	case 'A': {
	    /* 9 semitones above C */
	    scale_index = ET_SCALE_C + 9;
	    break;
	}
    case 'b':
	case 'B': {
	    /* 11 semitones above C */
	    scale_index = ET_SCALE_C + 11;
	    break;
	}
        default:
	    { /* unknown symbol --> no change */
		return M2F_UNKOWN;
	    }
    }

    if(  melody[pos] > 'Z' ) {  /* lower case chars have higher ASCII codes than A-Z */
         scale_index += 12;     /* shift one octave up */
    }

    return et_scale[scale_index];
}