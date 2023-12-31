#include "stdio.h"
#include "pico/stdlib.h"
#include "aht21.h"

const uint8_t LED = 20U;
AHT21 s;

int main()
{
	stdio_init_all();
	gpio_init(LED);
	gpio_set_dir(LED, true);

	i2c_init(i2c0, 100 * 1000);
	gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
	gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
	gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
	gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

	sleep_ms(5000);
	while(!AHT21_init(&s, i2c0))
	{
		printf("AHT21:Init failed\n");
		sleep_ms(3000);
	}

	while (1)
	{
		gpio_put(LED, !gpio_get(LED));
		
		AHT21_get_temperature(&s);
		AHT21_get_humidity(&s);

		// printf("Temp:\t%.2fC and Humi:\t%.2f\n",s.temperature,s.humidity);

		printf("/*%.2f,%.2f*/\n",s.temperature,s.humidity);
		sleep_ms(11);
	}

	return 0;
}