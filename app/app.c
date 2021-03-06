#include "stm32f4xx_hal.h"
#include "gpio.h"
#include "app.h"
#include "event_dispatcher.h"
#include "shell.h"
#include "mainloop_timer.h"
#include "blinky.h"
#include "motor.h"
#include "accelgyro.h"
#include "magneto.h"
#include "micros.h"
#include "imu.h"
#include "rx.h"
#include "baro.h"
#include "gps.h"
#include "flight.h"
#include "config.h"

void
app_init_f(void)
{
  event_dispatcher_init();
  mainloop_timer_init();
}

void
app_init(void)
{
  config_init();
  blinky_init();
  micros_init();
}

void
app_start(void)
{
  motor_init();

  accelgyro_init(sensor_align_cw_180, sensor_align_cw_180);
  accelgyro_start();

  magneto_init(sensor_align_cw_0);
  magneto_start();

  baro_init();
  baro_start();

  rx_init();
  gps_init();

  imu_init();

  flight_init();

  __disable_irq();
  shell_init();
  __enable_irq();
}

void
app_loop(void)
{
  while(1)
  {
    event_dispatcher_dispatch();
  }
}
