#ifndef ArduboyCore_h
#define ArduboyCore_h

#include <avr/power.h>
#include <SPI.h>
#include <avr/sleep.h>
#include <limits.h>


// main hardware compile flags

#if !defined(ARDUBOY_10) && !defined(AB_DEVKIT)
/// defaults to Arduboy Release 1.0 if not using a boards.txt file
/**
 * we default to Arduboy Release 1.0 if a compile flag has not been
 * passed to us from a boards.txt file
 *
 * if you wish to compile for the devkit without using a boards.txt
 * file simply comment out the ARDUBOY_10 define and uncomment
 * the AB_DEVKIT define like this:
 *
 *     // #define ARDUBOY_10
 *     #define AB_DEVKIT
 */     
#define ARDUBOY_10   //< compile for the production Arduboy v1.0
// #define AB_DEVKIT    //< compile for the official dev kit
#endif


#ifdef AB_DEVKIT
#define DEVKIT       //< for compatibilty with older sketches
#define SAFE_MODE    //< include safe mode (44 bytes)
#endif 


#ifdef ARDUBOY_10

#if defined AB_ALTERNATE_WIRING //Pro Micro Alternative OLED CS & RST pins
  #define CS 1
  #define RST 2
#else
  #define CS 12
  #define RST 6
#endif
#define DC 4
#if defined (OLED_SSD1306_I2C) || (OLED_SSD1306_I2CX) || (OLED_SH1106_I2C)
 //bitbanged I2C pins
 #define I2C_PORT  PORTD
 #define I2C_DDR   DDRD
 #define I2C_PIN   PIND
 #ifdef AB_ALTERNATE_WIRING
  #define SCL 1
  #define I2C_SCL PORTD3
 #else
  #define SCL 6
  #define I2C_SCL PORTD7
 #endif
 #define SDA 4
 #define I2C_SDA PORTD4 
  
 //port states
 #define I2C_SDA_HIGH() I2C_PORT |=  (1 << I2C_SDA)
 #define I2C_SCL_HIGH() I2C_PORT |=  (1 << I2C_SCL)
 #define I2C_SDA_LOW()  I2C_PORT &= ~(1 << I2C_SDA)
 #define I2C_SCL_LOW()  I2C_PORT &= ~(1 << I2C_SCL)
 
 //port directions
 #define I2C_SDA_AS_INPUT()  I2C_DDR &= ~(1 << I2C_SDA)
 #define I2C_SCL_AS_INPUT()  I2C_DDR &= ~(1 << I2C_SCL)
 #define I2C_SDA_AS_OUTPUT() I2C_DDR |= (1 << I2C_SDA)
 #define I2C_SCL_AS_OUTPUT() I2C_DDR |= (1 << I2C_SCL)
 
 // display address, commands
 #define SSD1306_I2C_ADDR 0x3c //0x3c:default, 0x3d: alternative)
 #define SSD1306_I2C_CMD  0x00
 #define SSD1306_I2C_DATA 0x40
#endif

#define RED_LED 10
#if defined AB_ALTERNATE_WIRING  //Pro Micro Alternative GREEN LED pin
  #define GREEN_LED 3
#else
  #define GREEN_LED 11
#endif
#define BLUE_LED 9
#define TX_LED 30
#define RX_LED 17

// pin values for buttons, probably shouldn't use these
#define PIN_LEFT_BUTTON A2
#define PIN_RIGHT_BUTTON A1
#define PIN_UP_BUTTON A0
#define PIN_DOWN_BUTTON A3
#define PIN_A_BUTTON 7
#define PIN_B_BUTTON 8

// bit values for button states
#define LEFT_BUTTON _BV(5)
#define RIGHT_BUTTON _BV(6)
#define UP_BUTTON _BV(7)
#define DOWN_BUTTON _BV(4)
#define A_BUTTON _BV(3)
#define B_BUTTON _BV(2)

#define PIN_SPEAKER_1 5
#define PIN_SPEAKER_1_PORT &PORTC
#define PIN_SPEAKER_1_BITMASK _BV(6)

#if defined AB_ALTERNATE_WIRING  //Pro Micro alternative for 2nd speaker pin
  #define PIN_SPEAKER_2 6
  #define PIN_SPEAKER_2_PORT &PORTD
  #define PIN_SPEAKER_2_BITMASK _BV(7)
#else
  #define PIN_SPEAKER_2 13
  #define PIN_SPEAKER_2_PORT &PORTC
  #define PIN_SPEAKER_2_BITMASK _BV(7)
#endif

#elif defined(AB_DEVKIT)

#define CS 6
#define DC 4
#define RST 12

// map all LEDs to the single TX LED on DEVKIT
#define RED_LED 17
#define GREEN_LED 17
#define BLUE_LED 17
#define TX_LED 17
#define RX_LED 17

// pin values for buttons, probably shouldn't use these
#define PIN_LEFT_BUTTON 9
#define PIN_RIGHT_BUTTON 5
#define PIN_UP_BUTTON 8
#define PIN_DOWN_BUTTON 10
#define PIN_A_BUTTON A0
#define PIN_B_BUTTON A1

// bit values for button states
#define LEFT_BUTTON _BV(5)
#define RIGHT_BUTTON _BV(2)
#define UP_BUTTON _BV(4)
#define DOWN_BUTTON _BV(6)
#define A_BUTTON _BV(1)
#define B_BUTTON _BV(0)

#define PIN_SPEAKER_1 A2
#define PIN_SPEAKER_2 A3

#define PIN_SPEAKER_1_PORT &PORTF
#define PIN_SPEAKER_2_PORT &PORTF

#define PIN_SPEAKER_1_BITMASK _BV(5)
#define PIN_SPEAKER_2_BITMASK _BV(4)

#endif

#define OLED_PIXELS_INVERTED 0xA7 // All pixels inverted (Same for SH1106)
#define OLED_PIXELS_NORMAL 0xA6 // All pixels normal (Same for SH1106)    

#define OLED_ALL_PIXELS_ON 0xA5 // all pixels on (Same for SH1106)
#define OLED_PIXELS_FROM_RAM 0xA4 // pixels mapped to display RAM contents (Same for SH1106)

#define OLED_VERTICAL_FLIPPED 0xC0 // reversed COM scan direction (Same for SH1106)
#define OLED_VERTICAL_NORMAL 0xC8 // normal COM scan direction (Same for SH1106)

#define OLED_SET_PAGE_ADDRESS      0xB0 // (Same for SH1106)
#if defined(OLED_SH1106) || defined(OLED_SH1106_I2C)
  #define OLED_SET_COLUMN_ADDRESS_LO 0x02 //SH1106: 1st pixel starts on column 2
#else
  #define OLED_SET_COLUMN_ADDRESS_LO 0x00 
#endif
#define OLED_SET_COLUMN_ADDRESS_HI 0x10 //(Same for SH1106)

// -----

#define COLUMN_ADDRESS_END (WIDTH - 1) & 0x7F   // 128 pixels wide
#define PAGE_ADDRESS_END ((HEIGHT/8)-1) & 0x07  // 8 pages high

#if defined (OLED_96X96) || (OLED_96X96_ON_128X128)
  #define WIDTH 96
#else
  #define WIDTH 128 //The standard width of the display in pixels
#endif    
#if defined(OLED_128X128)
  #define HEIGHT 128
#elif defined(OLED_96X96) || defined(OLED_128X96) || defined(OLED_96X96_ON_128X128) || defined(OLED_128X96_ON_128X128)
  #define HEIGHT 96
#else
  #define HEIGHT 64 //The standard height of the display in pixels
#endif

#define INVERT 2 //< lit/unlit pixel
#define WHITE 1 //< lit pixel
#define BLACK 0 //< unlit pixel

class ArduboyCore
{
public:
    ArduboyCore();

    /// allows the CPU to idle between frames
    /**
     * This puts the CPU in "Idle" sleep mode.  You should call this as often
     * as you can for the best power savings.  The timer 0 overflow interrupt
     * will wake up the chip every 1ms - so even at 60 FPS a well written
     * app should be able to sleep maybe half the time in between rendering
     * it's own frames.
     * 
     * See the Arduboy class nextFrame() for an example of how to use idle()
     * in a frame loop.
     */
    void static idle();
#if defined(GU12864_800B)    
    void static displayEnable();
    
    void static displayDisable();
    
    void static displayWrite(uint8_t data);
#endif
    void static LCDDataMode(); //< put the display in data mode

    /// put the display in command mode
    /**
     * See SSD1306 documents for available commands and command sequences.
     * 
     * Links:
     * - https://www.adafruit.com/datasheets/SSD1306.pdf
     * - http://www.eimodule.com/download/SSD1306-OLED-Controller.pdf
     */
    void static LCDCommandMode();

#if defined (OLED_SSD1306_I2C) || (OLED_SSD1306_I2CX) || (OLED_SH1106_I2C)
    void static i2c_start(uint8_t mode);
    void static inline i2c_stop() __attribute__((always_inline))
    {
      // SDA and SCL both are already low, from writing ACK bit no need to change state
      I2C_SDA_AS_INPUT(); // switch to input so SDA is pulled up externally first for stop condition
      I2C_SCL_AS_INPUT(); // pull up SCL externally
    }
    
    void static i2c_sendByte(uint8_t byte);
#endif
    
    uint8_t static width();    //< return display width
    uint8_t static height();   // < return display height
    
    /// get current state of all buttons (bitmask)
    /**
     * Bit mask that is returned:
     *
     *           Hi   Low   
     *  DevKit   00000000    - reserved                         
     *           -DLU-RAB    D down
     *                       U up       
     *  1.0      00000000    L left
     *           URLDAB--    R right
     * 
     * Of course you shouldn't worry about bits (they may change with future
     * hardware revisions) and should instead use the button defines:
     * LEFT_BUTTON, A_BUTTON, UP_BUTTON, etc.
     */

    uint8_t static getInput(); __attribute__ ((deprecated("use buttonsState() instead")));
    uint8_t static buttonsState();

    // paints 8 pixels (vertically) from a single byte
    //  - 1 is lit, 0 is unlit
    //
    // NOTE: You probably wouldn't actually use this, you'd build something
    // higher level that does it's own calls to SPI.transfer().  It's
    // included for completeness since it seems there should be some very
    // rudimentary low-level draw function in the core that supports the
    // minimum unit that the hardware allows (which is a strip of 8 pixels)
    //
    // This routine starts in the top left and then across the screen.
    // After each "page" (row) of 8 pixels is drawn it will shift down
    // to start drawing the next page.  To paint the full screen you call
    // this function 1,024 times.
    //
    // Example:
    //
    // X = painted pixels, . = unpainted
    //
    // blank()                      paint8Pixels() 0xFF, 0, 0x0F, 0, 0xF0
    // v TOP LEFT corner (8x9)      v TOP LEFT corner
    // ........ (page 1)            X...X... (page 1)
    // ........                     X...X...
    // ........                     X...X...
    // ........                     X...X...
    // ........                     X.X.....
    // ........                     X.X.....
    // ........                     X.X.....
    // ........ (end of page 1)     X.X..... (end of page 1)
    // ........ (page 2)            ........ (page 2)
    void static paint8Pixels(uint8_t pixels);

    /// paints an entire image directly to hardware (from PROGMEM)
    /*
     * Each byte will be 8 vertical pixels, painted in the same order as
     * explained above in paint8Pixels.
     */
    void static paintScreen(const unsigned char *image);

    /// paints an entire image directly to hardware (from RAM)
    /*
     * Each byte will be 8 vertical pixels, painted in the same order as
     * explained above in paint8Pixels.
     */
    void static paintScreen(unsigned char image[]);

    /// paints a blank (black) screen to hardware
    void static blank();

    /// invert the display or set to normal
    /**
     * when inverted, a pixel set to 0 will be on
     */
    void static invert(boolean inverse);

    /// turn all display pixels on, or display the buffer contents
    /**
     * when set to all pixels on, the display buffer will be
     * ignored but not altered
     */
    void static allPixelsOn(boolean on);

    /// flip the display vertically or set to normal
    void static flipVertical(boolean flipped);

    /// flip the display horizontally or set to normal
    void static flipHorizontal(boolean flipped);

    /// send a single byte command to the OLED
    void static sendLCDCommand(uint8_t command);

    /// set the light output of the RGB LEB
    void setRGBled(uint8_t red, uint8_t green, uint8_t blue);

protected:
    /// boots the hardware
    /**
     * - sets input/output/pullup mode for pins
     * - powers up the OLED screen and initializes it properly
     * - sets up power saving
     * - kicks CPU down to 8Mhz if needed
     * - allows Safe mode to be entered
     */
    void static boot();

    /// Safe mode
    /**
     * Safe Mode is engaged by holding down both the LEFT button and UP button
     * when plugging the device into USB.  It puts your device into a tight
     * loop and allows it to be reprogrammed even if you have uploaded a very
     * broken sketch that interferes with the normal USB triggered auto-reboot
     * functionality of the device.
     * 
     * This is most useful on Devkits because they lack a built-in reset
     * button.
     */
    void static inline safeMode() __attribute__((always_inline));

    // internals
    void static inline bootLCD() __attribute__((always_inline));
    void static inline bootPins() __attribute__((always_inline));
    void static inline slowCPU() __attribute__((always_inline));
    void static inline saveMuchPower(); __attribute__((always_inline));


private:
    volatile static uint8_t *mosiport,  *csport, *dcport;
    uint8_t static mosipinmask, cspinmask, dcpinmask;

};

#endif
