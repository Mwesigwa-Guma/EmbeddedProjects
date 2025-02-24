
#include "unity.h"
#include "adc.h"
#include <avr/io.h>

void setUp(void) {
    // Set up code here
}

void tearDown(void) {
    // Tear down code here
}

void test_adc_init(void) {
    /*adc_init();
    TEST_ASSERT_TRUE(ADMUX & (1 << REFS0));
    TEST_ASSERT_TRUE(ADCSRA & (1 << ADEN));
    TEST_ASSERT_TRUE(ADCSRA & (1 << ADPS2));
    TEST_ASSERT_TRUE(ADCSRA & (1 << ADPS1));
    TEST_ASSERT_TRUE(ADCSRA & (1 << ADPS0));*/
}

void test_adc_read(void) {
    /*uint8_t channel = 0;
    ADMUX = 0x00;
    ADCSRA = (1 << ADSC);
    adc_read(channel);
    TEST_ASSERT_EQUAL(channel, ADMUX & 0x07);
    TEST_ASSERT_TRUE(ADCSRA & (1 << ADSC));*/

}