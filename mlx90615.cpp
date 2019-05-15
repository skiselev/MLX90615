/*************************************************************************
 * A minimal Arduino library for
 * Melexis MLX90615 Infra-red Temperature Sensor
 * Copyright (C) 2017 Sergey Kiselev
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *************************************************************************/
 
 #include "mlx90615.h"

MLX90615::MLX90615(uint8_t i2c_addr) {
  i2c_addr_ = i2c_addr;
}

void MLX90615::begin() {
  Wire.begin();
}

uint32_t MLX90615::get_id() {
	uint32_t id;
	
	id = read_word16(MLX90615_REG_ID_LOW);
	id |= (uint32_t)read_word16(MLX90615_REG_ID_HIGH) << 16;

	return id;
}

float MLX90615::get_ambient_temp() {
  float temp;

  temp = read_word16(MLX90615_REG_TEMP_AMBIENT) * 0.02 - 273.15;
  
  return temp;
}

float MLX90615::get_object_temp() {
  float temp;

  temp = read_word16(MLX90615_REG_TEMP_OBJECT) * 0.02 - 273.15;
  
  return temp;
}

uint16_t MLX90615::read_word16(uint8_t reg) {
  uint16_t data;
#ifdef __SAM3X8E__ 
  Wire.requestFrom(i2c_addr_, 3, reg, 1, true); 
#else
  Wire.beginTransmission(i2c_addr_);
  Wire.write(reg);
  Wire.endTransmission(false);
  
  Wire.requestFrom(i2c_addr_, (uint8_t)3);
#endif
  data = Wire.read();       // read low byte
  data |= Wire.read() << 8; // read high byte

  Wire.read(); // read and discard PEC (packet error code)

  return data;
}
