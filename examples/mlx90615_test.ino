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
 
#include <Wire.h>
#include <mlx90615.h>

MLX90615 mlx = MLX90615();

void setup() {
  Serial.begin(9600);
  Serial.println("Melexis MLX90615 infra-red temperature sensor test");
  mlx.begin();
  Serial.print("Sensor ID number = ");
  Serial.println(mlx.get_id(), HEX);
}

void loop() {
  Serial.print("Ambient = ");
  Serial.print(mlx.get_ambient_temp()); 
  Serial.print(" *C\tObject = ");
  Serial.print(mlx.get_object_temp());
  Serial.println(" *C");

  Serial.println();
  delay(500);
}