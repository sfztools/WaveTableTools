#!/bin/sh
# A shell script conversion of the generator from futur3soundz WTableTools_101.zip
# SPDX-License-Identifier: proprietary

set -e
set -x

mkdir -p Sines
WCreate 1024 "1," 					Sines/sine.wav
WCreate 1024 "1,1" 					Sines/sine_1_2.wav
WCreate 1024 "1,0.75" 				Sines/sine_1_2a.wav
WCreate 1024 "1,0.5" 				Sines/sine_1_2b.wav
WCreate 1024 "1,0.25" 				Sines/sine_1_2c.wav
WCreate 1024 "1,-1" 				Sines/sine_1_2d.wav
WCreate 1024 "1,-0.5" 				Sines/sine_1_2e.wav
WCreate 1024 "1,-0.25" 				Sines/sine_1_2f.wav
WCreate 1024 "1,1,1" 				Sines/sine_1_2_3.wav
WCreate 1024 "1,1,0.75" 			Sines/sine_1_2_3a.wav
WCreate 1024 "1,1,0.5" 				Sines/sine_1_2_3b.wav
WCreate 1024 "1,1,0.25" 			Sines/sine_1_2_3c.wav
WCreate 1024 "1,1,1,1" 				Sines/sine_1_2_3_4.wav
WCreate 1024 "1,1,1,0.75" 			Sines/sine_1_2_3_4a.wav
WCreate 1024 "1,1,1,0.5" 			Sines/sine_1_2_3_4b.wav
WCreate 1024 "1,1,1,0.25" 			Sines/sine_1_2_3_4c.wav
WCreate 1024 "1,1,1,1,1" 			Sines/sine_1_2_3_4_5.wav
WCreate 1024 "1,1,1,1,0.75" 		Sines/sine_1_2_3_4_5a.wav
WCreate 1024 "1,1,1,1,0.5" 			Sines/sine_1_2_3_4_5b.wav
WCreate 1024 "1,1,1,1,0.25" 		Sines/sine_1_2_3_4_5c.wav
WCreate 1024 "1,1,1,1,1,1" 			Sines/sine_1_2_3_4_5_6.wav
WCreate 1024 "1,1,1,1,1,0.75" 		Sines/sine_1_2_3_4_5_6a.wav
WCreate 1024 "1,1,1,1,1,0.5" 		Sines/sine_1_2_3_4_5_6b.wav
WCreate 1024 "1,1,1,1,1,0.25"		Sines/sine_1_2_3_4_5_6c.wav
WCreate 1024 "1,1,1,1,1,1,1" 		Sines/sine_1_2_3_4_5_6_7.wav
WCreate 1024 "1,1,1,1,1,1,0.75" 	Sines/sine_1_2_3_4_5_6_7a.wav
WCreate 1024 "1,1,1,1,1,1,0.5" 		Sines/sine_1_2_3_4_5_6_7b.wav
WCreate 1024 "1,1,1,1,1,1,0.25" 	Sines/sine_1_2_3_4_5_6_7c.wav
WCreate 1024 "1,,1" 				Sines/sine_1_3.wav
WCreate 1024 "1,,0.75" 				Sines/sine_1_3a.wav
WCreate 1024 "1,,0.5" 				Sines/sine_1_3b.wav
WCreate 1024 "1,,0.25" 				Sines/sine_1_3c.wav
WCreate 1024 "1,,-1" 				Sines/sine_1_3d.wav
WCreate 1024 "1,,-0.5" 				Sines/sine_1_3e.wav
WCreate 1024 "1,,-0.25" 			Sines/sine_1_3f.wav
WCreate 1024 "1,,,1" 				Sines/sine_1_4.wav
WCreate 1024 "1,,,0.75" 			Sines/sine_1_4a.wav
WCreate 1024 "1,,,0.5" 				Sines/sine_1_4b.wav
WCreate 1024 "1,,,0.25" 			Sines/sine_1_4c.wav
WCreate 1024 "1,,,-1" 				Sines/sine_1_4d.wav
WCreate 1024 "1,,,-0.5" 			Sines/sine_1_4e.wav
WCreate 1024 "1,,,-0.25"			Sines/sine_1_4f.wav
WCreate 1024 "1,,,,1" 				Sines/sine_1_5.wav
WCreate 1024 "1,,,,0.75" 			Sines/sine_1_5a.wav
WCreate 1024 "1,,,,0.5" 			Sines/sine_1_5b.wav
WCreate 1024 "1,,,,0.25" 			Sines/sine_1_5c.wav
WCreate 1024 "1,,,,-1" 				Sines/sine_1_5d.wav
WCreate 1024 "1,,,,-0.5" 			Sines/sine_1_5e.wav
WCreate 1024 "1,,,,-0.25"			Sines/sine_1_5f.wav
WCreate 1024 "1,,,,,1" 				Sines/sine_1_6.wav
WCreate 1024 "1,,,,,0.75" 			Sines/sine_1_6a.wav
WCreate 1024 "1,,,,,0.5" 			Sines/sine_1_6b.wav
WCreate 1024 "1,,,,,0.25" 			Sines/sine_1_6c.wav
WCreate 1024 "1,,,,,-1" 			Sines/sine_1_6d.wav
WCreate 1024 "1,,,,,-0.5" 			Sines/sine_1_6e.wav
WCreate 1024 "1,,,,,-0.25"			Sines/sine_1_6f.wav
WCreate 1024 "1,,,,,1" 				Sines/sine_1_7.wav
WCreate 1024 "1,,,,,,0.75" 			Sines/sine_1_7a.wav
WCreate 1024 "1,,,,,,0.5" 			Sines/sine_1_7b.wav
WCreate 1024 "1,,,,,,0.25" 			Sines/sine_1_7c.wav
WCreate 1024 "1,,,,,,-1" 			Sines/sine_1_7d.wav
WCreate 1024 "1,,,,,,-0.5" 			Sines/sine_1_7e.wav
WCreate 1024 "1,,,,,,-0.25"			Sines/sine_1_7f.wav
WCreate 1024 "1,,,,,,,1" 			Sines/sine_1_8.wav
WCreate 1024 "1,,,,,,,0.75" 		Sines/sine_1_8a.wav
WCreate 1024 "1,,,,,,,0.5" 			Sines/sine_1_8b.wav
WCreate 1024 "1,,,,,,,0.25" 		Sines/sine_1_8c.wav
WCreate 1024 "1,,,,,,,-1" 			Sines/sine_1_8d.wav
WCreate 1024 "1,,,,,,,-0.5" 		Sines/sine_1_8e.wav
WCreate 1024 "1,,,,,,,-0.25"		Sines/sine_1_8f.wav
WCreate 1024 "1,,,,,,,,1" 			Sines/sine_1_9.wav
WCreate 1024 "1,,,,,,,,0.75" 		Sines/sine_1_9a.wav
WCreate 1024 "1,,,,,,,,0.5" 		Sines/sine_1_9b.wav
WCreate 1024 "1,,,,,,,,0.25" 		Sines/sine_1_9c.wav
WCreate 1024 "1,,,,,,,,-1" 			Sines/sine_1_9d.wav
WCreate 1024 "1,,,,,,,,-0.5" 		Sines/sine_1_9e.wav
WCreate 1024 "1,,,,,,,,-0.25"		Sines/sine_1_8f.wav
WCreate 1024 "1,,,,,,,,,1" 			Sines/sine_1_10.wav
WCreate 1024 "1,,,,,,,,,0.75" 		Sines/sine_1_10a.wav
WCreate 1024 "1,,,,,,,,,0.5" 		Sines/sine_1_10b.wav
WCreate 1024 "1,,,,,,,,,0.25" 		Sines/sine_1_10c.wav
WCreate 1024 "1,,,,,,,,,-1"			Sines/sine_1_10d.wav
WCreate 1024 "1,,,,,,,,,-0.5" 		Sines/sine_1_10e.wav
WCreate 1024 "1,,,,,,,,,-0.25"		Sines/sine_1_10f.wav
WCreate 1024 "1,,,,,,,,,,,1" 		Sines/sine_1_12.wav
WCreate 1024 "1,,,,,,,,,,,0.75" 	Sines/sine_1_12a.wav
WCreate 1024 "1,,,,,,,,,,,0.5" 		Sines/sine_1_12b.wav
WCreate 1024 "1,,,,,,,,,,,0.25" 	Sines/sine_1_12c.wav
WCreate 1024 "1,,,,,,,,,,,-1"		Sines/sine_1_12d.wav
WCreate 1024 "1,,,,,,,,,,,-0.5" 	Sines/sine_1_12e.wav
WCreate 1024 "1,,,,,,,,,,,-0.25"	Sines/sine_1_12f.wav
WCreate 1024 "1,1,1" 				Sines/sine_1_2_3.wav
WCreate 1024 "1,1,0.75"				Sines/sine_1_2_3a.wav
WCreate 1024 "1,1,0.5" 				Sines/sine_1_2_3b.wav
WCreate 1024 "1,1,0.25"				Sines/sine_1_2_3c.wav
WCreate 1024 "1,1,-1"				Sines/sine_1_2_3d.wav
WCreate 1024 "1,1,-0.5"				Sines/sine_1_2_3e.wav
WCreate 1024 "1,1,-0.25" 			Sines/sine_1_2_3f.wav
WCreate 1024 "1,1,,1" 				Sines/sine_1_2_4.wav
WCreate 1024 "1,1,,0.75" 			Sines/sine_1_2_4a.wav
WCreate 1024 "1,1,,0.5"				Sines/sine_1_2_4b.wav
WCreate 1024 "1,1,,0.25" 			Sines/sine_1_2_4c.wav
WCreate 1024 "1,1,,-1" 				Sines/sine_1_2_4d.wav
WCreate 1024 "1,1,,-0.5" 			Sines/sine_1_2_4e.wav
WCreate 1024 "1,1,,-0.25"			Sines/sine_1_2_4f.wav
WCreate 1024 "1,1,,,1" 				Sines/sine_1_2_5.wav
WCreate 1024 "1,1,,,0.75" 			Sines/sine_1_2_5a.wav
WCreate 1024 "1,1,,,0.5" 			Sines/sine_1_2_5b.wav
WCreate 1024 "1,1,,,0.25" 			Sines/sine_1_2_5c.wav
WCreate 1024 "1,1,,,-1" 			Sines/sine_1_2_5d.wav
WCreate 1024 "1,1,,,-0.5" 			Sines/sine_1_2_5e.wav
WCreate 1024 "1,1,,,-0.25"			Sines/sine_1_2_5f.wav
WCreate 1024 "1,1,,,,1" 			Sines/sine_1_2_6.wav
WCreate 1024 "1,1,,,,0.75" 			Sines/sine_1_2_6a.wav
WCreate 1024 "1,1,,,,0.5" 			Sines/sine_1_2_6b.wav
WCreate 1024 "1,1,,,,0.25" 			Sines/sine_1_2_6c.wav
WCreate 1024 "1,1,,,,-1" 			Sines/sine_1_2_6d.wav
WCreate 1024 "1,1,,,,-0.5" 			Sines/sine_1_2_6e.wav
WCreate 1024 "1,1,,,,-0.25"			Sines/sine_1_2_6f.wav
WCreate 1024 "1,1,,,,1" 			Sines/sine_1_2_7.wav
WCreate 1024 "1,1,,,,,0.75" 		Sines/sine_1_2_7a.wav
WCreate 1024 "1,1,,,,,0.5" 			Sines/sine_1_2_7b.wav
WCreate 1024 "1,1,,,,,0.25" 		Sines/sine_1_2_7c.wav
WCreate 1024 "1,1,,,,,-1" 			Sines/sine_1_2_7d.wav
WCreate 1024 "1,1,,,,,-0.5" 		Sines/sine_1_2_7e.wav
WCreate 1024 "1,1,,,,,-0.25"		Sines/sine_1_2_7f.wav
WCreate 1024 "1,1,,,,,,1" 			Sines/sine_1_2_8.wav
WCreate 1024 "1,1,,,,,,0.75" 		Sines/sine_1_2_8a.wav
WCreate 1024 "1,1,,,,,,0.5" 		Sines/sine_1_2_8b.wav
WCreate 1024 "1,1,,,,,,0.25" 		Sines/sine_1_2_8c.wav
WCreate 1024 "1,1,,,,,,-1" 			Sines/sine_1_2_8d.wav
WCreate 1024 "1,1,,,,,,-0.5" 		Sines/sine_1_2_8e.wav
WCreate 1024 "1,1,,,,,,-0.25"		Sines/sine_1_2_8f.wav
WCreate 1024 "1,1,,,,,,,1" 			Sines/sine_1_2_9.wav
WCreate 1024 "1,1,,,,,,,0.75" 		Sines/sine_1_2_9a.wav
WCreate 1024 "1,1,,,,,,,0.5" 		Sines/sine_1_2_9b.wav
WCreate 1024 "1,1,,,,,,,0.25" 		Sines/sine_1_2_9c.wav
WCreate 1024 "1,1,,,,,,,-1" 		Sines/sine_1_2_9d.wav
WCreate 1024 "1,1,,,,,,,-0.5" 		Sines/sine_1_2_9e.wav
WCreate 1024 "1,1,,,,,,,-0.25"		Sines/sine_1_2_8f.wav
WCreate 1024 "1,1,,,,,,,,1" 		Sines/sine_1_2_10.wav
WCreate 1024 "1,1,,,,,,,,0.75" 		Sines/sine_1_2_10a.wav
WCreate 1024 "1,1,,,,,,,,0.5" 		Sines/sine_1_2_10b.wav
WCreate 1024 "1,1,,,,,,,,0.25" 		Sines/sine_1_2_10c.wav
WCreate 1024 "1,1,,,,,,,,-1"		Sines/sine_1_2_10d.wav
WCreate 1024 "1,1,,,,,,,,-0.5" 		Sines/sine_1_2_10e.wav
WCreate 1024 "1,1,,,,,,,,-0.25"		Sines/sine_1_2_10f.wav
WCreate 1024 "1,1,,,,,,,,,,1" 		Sines/sine_1_2_12.wav
WCreate 1024 "1,1,,,,,,,,,,0.75" 	Sines/sine_1_2_12a.wav
WCreate 1024 "1,1,,,,,,,,,,0.5" 	Sines/sine_1_2_12b.wav
WCreate 1024 "1,1,,,,,,,,,,0.25" 	Sines/sine_1_2_12c.wav
WCreate 1024 "1,1,,,,,,,,,,-1"		Sines/sine_1_2_12d.wav
WCreate 1024 "1,1,,,,,,,,,,-0.5" 	Sines/sine_1_2_12e.wav
WCreate 1024 "1,1,,,,,,,,,,-0.25"	Sines/sine_1_2_12f.wav
WCreate 1024 "x<180" 				Sines/sine_hrm_180.wav
WCreate 1024 "x<160" 				Sines/sine_hrm_160.wav
WCreate 1024 "x<140" 				Sines/sine_hrm_140.wav
WCreate 1024 "x<120" 				Sines/sine_hrm_120.wav
WCreate 1024 "x<100" 				Sines/sine_hrm_100.wav
WCreate 1024 "x<95" 				Sines/sine_hrm_95.wav
WCreate 1024 "x<90" 				Sines/sine_hrm_90.wav
WCreate 1024 "x<85" 				Sines/sine_hrm_85.wav
WCreate 1024 "x<80" 				Sines/sine_hrm_80.wav
WCreate 1024 "x<75" 				Sines/sine_hrm_75.wav
WCreate 1024 "x<70" 				Sines/sine_hrm_70.wav
WCreate 1024 "x<65" 				Sines/sine_hrm_65.wav
WCreate 1024 "x<60" 				Sines/sine_hrm_60.wav
WCreate 1024 "x<55" 				Sines/sine_hrm_55.wav
WCreate 1024 "x<50" 				Sines/sine_hrm_50.wav
WCreate 1024 "x<45" 				Sines/sine_hrm_45.wav
WCreate 1024 "x<40" 				Sines/sine_hrm_40.wav
WCreate 1024 "x<35" 				Sines/sine_hrm_35.wav
WCreate 1024 "x<30" 				Sines/sine_hrm_30.wav
WCreate 1024 "x<25" 				Sines/sine_hrm_25.wav
WCreate 1024 "x<20" 				Sines/sine_hrm_20.wav
WCreate 1024 "x<15" 				Sines/sine_hrm_15.wav
WCreate 1024 "x<10" 				Sines/sine_hrm_10.wav
WCreate 1024 "x<8" 					Sines/sine_hrm_08.wav
WCreate 1024 "x<6" 					Sines/sine_hrm_06.wav


mkdir -p Saws
WCreate 1024 "1/x" 					Saws/saw.wav
WCreate 1024 "1/x*(x<256)" 			Saws/saw_256.wav
WCreate 1024 "1/x*(x<128)" 			Saws/saw_128.wav
WCreate 1024 "1/x*(x<96)" 			Saws/saw_96.wav
WCreate 1024 "1/x*(x<64)" 			Saws/saw_64.wav
WCreate 1024 "1/x*(x<48)" 			Saws/saw_48.wav
WCreate 1024 "1/x*(x<32)" 			Saws/saw_32.wav
WCreate 1024 "1/x*(x<24)" 			Saws/saw_24.wav
WCreate 1024 "1/x*(x<16)" 			Saws/saw_16.wav
WCreate 1024 "1/x*(x<12)" 			Saws/saw_12.wav
WCreate 1024 "1/x*(x<8)" 			Saws/saw_8.wav
WCreate 1024 "1/x*(x<6)" 			Saws/saw_6.wav
WCreate 1024 "1/x*(x<4)" 			Saws/saw_4.wav
WCreate 1024 "1/x*(x<2)" 			Saws/saw_2.wav
WCreate 1024 "1/x^1.45"				Saws/saw_dull_1.wav
WCreate 1024 "1/x^1.4" 				Saws/saw_dull_2.wav
WCreate 1024 "1/x^1.35" 			Saws/saw_dull_3.wav
WCreate 1024 "1/x^1.3"				Saws/saw_dull_4.wav
WCreate 1024 "1/x^1.25"				Saws/saw_dull_5.wav
WCreate 1024 "1/x^1.2"				Saws/saw_dull_6.wav
WCreate 1024 "1/x^1.15" 				Saws/saw_dull_7.wav
WCreate 1024 "1/x^1.1" 				Saws/saw_dull_8.wav
WCreate 1024 "1/x^1.05"				Saws/saw_dull_9.wav
WCreate 1024 "-1/x^1.05;(x=1)*-0.38+((x=2)*-0.075)+((x=3)*-0.019)" 	Saws/analog_saw_01.wav
WCreate 1024 "-1/x^1.10;(x=1)*-0.38+((x=2)*-0.075)+((x=3)*-0.019)" 	Saws/analog_saw_02.wav
WCreate 1024 "-1/x^1.15;(x=1)*-0.38+((x=2)*-0.075)+((x=3)*-0.019)" 	Saws/analog_saw_03.wav
WCreate 1024 "-1/x^1.2;(x=1)*-0.38+((x=2)*-0.075)+((x=3)*-0.019)" 	Saws/analog_saw_04.wav
WCreate 1024 "-1/x^1.25;(x=1)*-0.38+((x=2)*-0.075)+((x=3)*-0.019)" 	Saws/analog_saw_05.wav
WCreate 1024 "-1/x^1.3;(x=1)*-0.38+((x=2)*-0.075)+((x=3)*-0.019)" 	Saws/analog_saw_06.wav
WCreate 1024 "-1/x^1.35;(x=1)*-0.38+((x=2)*-0.075)+((x=3)*-0.019)" 	Saws/analog_saw_07.wav
WCreate 1024 "-1/x^1.4;(x=1)*-0.38+((x=2)*-0.075)+((x=3)*-0.019)" 	Saws/analog_saw_08.wav
WCreate 1024 "-1/x^1.45;(x=1)*-0.38+((x=2)*-0.075)+((x=3)*-0.019)" 	Saws/analog_saw_09.wav
WCreate 1024 "-1/x^1.5;(x=1)*-0.38+((x=2)*-0.075)+((x=3)*-0.019)" 	Saws/analog_saw_10.wav
WCreate 1024 "-1/x^0.5;(x=1)*-0.38+((x=2)*-0.075)+((x=3)*-0.019)" 	Saws/analog_saw_11.wav
WCreate 1024 "-1/x^0.55;(x=1)*-0.38+((x=2)*-0.075)+((x=3)*-0.019)" 	Saws/analog_saw_12.wav
WCreate 1024 "-1/x^0.6;(x=1)*-0.38+((x=2)*-0.075)+((x=3)*-0.019)" 	Saws/analog_saw_13.wav
WCreate 1024 "-1/x^0.65;(x=1)*-0.38+((x=2)*-0.075)+((x=3)*-0.019)" 	Saws/analog_saw_14.wav
WCreate 1024 "-1/x^0.7;(x=1)*-0.38+((x=2)*-0.075)+((x=3)*-0.019)" 	Saws/analog_saw_15.wav
WCreate 1024 "-1/x^0.75;(x=1)*-0.38+((x=2)*-0.075)+((x=3)*-0.019)" 	Saws/analog_saw_16.wav
WCreate 1024 "-1/x^0.8;(x=1)*-0.38+((x=2)*-0.075)+((x=3)*-0.019)" 	Saws/analog_saw_17.wav
WCreate 1024 "-1/x^0.85;(x=1)*-0.38+((x=2)*-0.075)+((x=3)*-0.019)" 	Saws/analog_saw_18.wav
WCreate 1024 "-1/x^0.9;(x=1)*-0.38+((x=2)*-0.075)+((x=3)*-0.019)" 	Saws/analog_saw_19.wav
WCreate 1024 "-1/x^0.95;(x=1)*-0.38+((x=2)*-0.075)+((x=3)*-0.019)" 	Saws/analog_saw_20.wav
WCreate 1024 "(0.9+0.1*#)/x"		Saws/noisy_saw_1.wav
WCreate 1024 "(0.8+0.1*#)/x"		Saws/noisy_saw_2.wav
WCreate 1024 "(0.7+0.2*#)/x"		Saws/noisy_saw_3.wav
WCreate 1024 "(0.6+0.3*#)/x"		Saws/noisy_saw_4.wav
WCreate 1024 "(0.5+0.4*#)/x"		Saws/noisy_saw_5.wav
WCreate 1024 "(0.4+0.5*#)/x"		Saws/noisy_saw_6.wav
WCreate 1024 "(0.3+0.6*#)/x"		Saws/noisy_saw_7.wav
WCreate 1024 "(0.2+0.7*#)/x"		Saws/noisy_saw_8.wav
WCreate 1024 "(0.1+0.8*#)/x"		Saws/noisy_saw_9.wav

mkdir -p Triangles
WCreate 1024 "1/x^2*((x%4=1)-((x+2)%4=1))"					Triangles/triangle.wav
WCreate 1024 "(1/x^2*((x%4=1)-((x+2)%4=1)))*(x<256)"			Triangles/triangle_256.wav
WCreate 1024 "(1/x^2*((x%4=1)-((x+2)%4=1)))*(x<128)"			Triangles/triangle_128.wav
WCreate 1024 "(1/x^2*((x%4=1)-((x+2)%4=1)))*(x<64)"			Triangles/triangle_64.wav
WCreate 1024 "(1/x^2*((x%4=1)-((x+2)%4=1)))*(x<32)"			Triangles/triangle_32.wav
WCreate 1024 "(1/x^2*((x%4=1)-((x+2)%4=1)))*(x<16)"			Triangles/triangle_16.wav
WCreate 1024 "(1/x^2*((x%4=1)-((x+2)%4=1)))*(x<8)"			Triangles/triangle_8.wav
WCreate 1024 "(1/x^2*((x%4=1)-((x+2)%4=1)))*(x<4)"			Triangles/triangle_4.wav

mkdir -p Squares
WCreate 1024 "1/x*(x%2)"					Squares/square.wav
WCreate 1024 "1/x^1.05*(x%2)"				Squares/square_dull_01.wav
WCreate 1024 "1/x^1.15*(x%2)"				Squares/square_dull_02.wav
WCreate 1024 "1/x^1.2*(x%2)"				Squares/square_dull_03.wav
WCreate 1024 "1/x^1.25*(x%2)"				Squares/square_dull_04.wav
WCreate 1024 "1/x^1.3*(x%2)"				Squares/square_dull_05.wav
WCreate 1024 "1/x^1.35*(x%2)"				Squares/square_dull_06.wav
WCreate 1024 "1/x^1.4*(x%2)"				Squares/square_dull_07.wav
WCreate 1024 "1/x^1.45*(x%2)"				Squares/square_dull_08.wav
WCreate 1024 "1/x^1.5*(x%2)"				Squares/square_dull_09.wav
WCreate 1024 "1/x^1.55*(x%2)"				Squares/square_dull_10.wav
WCreate 1024 "1/x*(x%2)-0.05*1/x*(x%2=0)"	Squares/square_slew_01.wav
WCreate 1024 "1/x*(x%2)-0.1*1/x*(x%2=0)"	Squares/square_slew_02.wav
WCreate 1024 "1/x*(x%2)-0.15*1/x*(x%2=0)"	Squares/square_slew_03.wav
WCreate 1024 "1/x*(x%2)-0.2*1/x*(x%2=0)"	Squares/square_slew_04.wav
WCreate 1024 "1/x*(x%2)-0.25*1/x*(x%2=0)"	Squares/square_slew_05.wav
WCreate 1024 "1/x*(x%2)-0.3*1/x*(x%2=0)"	Squares/square_slew_06.wav
WCreate 1024 "1/x*(x%2)-0.35*1/x*(x%2=0)"	Squares/square_slew_07.wav
WCreate 1024 "1/x*(x%2)-0.4*1/x*(x%2=0)"	Squares/square_slew_08.wav
WCreate 1024 "1/x*(x%2)-0.45*1/x*(x%2=0)"	Squares/square_slew_09.wav
WCreate 1024 "(x=1)*0.7+(x!=1)*1/x*(x%2)"	Squares/square_lo_first_01.wav
WCreate 1024 "(x=1)*0.75+(x!=1)*1/x*(x%2)"	Squares/square_lo_first_02.wav
WCreate 1024 "(x=1)*0.8+(x!=1)*1/x*(x%2)"	Squares/square_lo_first_03.wav
WCreate 1024 "(x=1)*0.85+(x!=1)*1/x*(x%2)"	Squares/square_lo_first_04.wav
WCreate 1024 "(x=1)*0.9+(x!=1)*1/x*(x%2)"	Squares/square_lo_first_05.wav
WCreate 1024 "(x=1)*0.95+(x!=1)*1/x*(x%2)"	Squares/square_lo_first_06.wav


mkdir -p Buzzes
WCreate 1024 "(x<6)+(x>17)&&(x<19)+(x>50)*0.015"		Buzzes/buzz_00.wav
WCreate 1024 "(x<6)+(x>19)&&(x<22)+(x>50)*0.015"		Buzzes/buzz_01.wav
WCreate 1024 "(x<6)+(x>21)&&(x<25)+(x>50)*0.015"		Buzzes/buzz_02.wav
WCreate 1024 "(x<6)+(x>23)&&(x<28)+(x>50)*0.015"		Buzzes/buzz_03.wav
WCreate 1024 "(x<6)+(x>25)&&(x<31)+(x>50)*0.015"		Buzzes/buzz_04.wav
WCreate 1024 "(x<6)+(x>27)&&(x<34)+(x>50)*0.015"		Buzzes/buzz_05.wav
WCreate 1024 "(x<6)+(x>29)&&(x<37)+(x>50)*0.015"		Buzzes/buzz_06.wav
WCreate 1024 "(x<6)+(x>31)&&(x<40)+(x>50)*0.015"		Buzzes/buzz_07.wav
WCreate 1024 "(x<6)+(x>33)&&(x<43)+(x>50)*0.015"		Buzzes/buzz_08.wav
WCreate 1024 "(x<4)+(x>35)&&(x<45)+(x>50)*0.015"		Buzzes/buzz_09.wav
WCreate 1024 "(x<4)+(x>17)&&(x<19)+(x>70)*0.015"		Buzzes/buzz_10.wav
WCreate 1024 "(x<4)+(x>19)&&(x<22)+(x>70)*0.015"		Buzzes/buzz_11.wav
WCreate 1024 "(x<4)+(x>21)&&(x<25)+(x>70)*0.015"		Buzzes/buzz_12.wav
WCreate 1024 "(x<4)+(x>23)&&(x<28)+(x>70)*0.015"		Buzzes/buzz_13.wav
WCreate 1024 "(x<4)+(x>25)&&(x<31)+(x>70)*0.015"		Buzzes/buzz_14.wav
WCreate 1024 "(x<4)+(x>27)&&(x<34)+(x>70)*0.015"		Buzzes/buzz_15.wav
WCreate 1024 "(x<4)+(x>29)&&(x<37)+(x>70)*0.015"		Buzzes/buzz_16.wav
WCreate 1024 "(x<4)+(x>31)&&(x<40)+(x>70)*0.015"		Buzzes/buzz_17.wav
WCreate 1024 "(x<4)+(x>33)&&(x<43)+(x>70)*0.015"		Buzzes/buzz_18.wav
WCreate 1024 "(x<4)+(x>35)&&(x<45)+(x>70)*0.015"		Buzzes/buzz_19.wav
WCreate 1024 "(x<4)+(x>37)&&(x<48)+(x>70)*0.015"		Buzzes/buzz_20.wav
WCreate 1024 "(x<4)+(x>39)&&(x<51)+(x>80)*0.015"		Buzzes/buzz_21.wav
WCreate 1024 "(x<4)+(x>41)&&(x<54)+(x>80)*0.015"		Buzzes/buzz_22.wav
WCreate 1024 "(x<4)+(x>43)&&(x<57)+(x>80)*0.015"		Buzzes/buzz_23.wav
WCreate 1024 "(x<4)+(x>45)&&(x<60)+(x>80)*0.015"		Buzzes/buzz_24.wav
WCreate 1024 "(x<4)+(x>47)&&(x<63)+(x>80)*0.015"		Buzzes/buzz_25.wav
WCreate 1024 "(x<4)+(x>49)&&(x<66)+(x>80)*0.015"		Buzzes/buzz_26.wav
WCreate 1024 "(x<4)+(x>51)&&(x<69)+(x>80)*0.015"		Buzzes/buzz_27.wav
WCreate 1024 "(x<4)+(x>53)&&(x<72)+(x>80)*0.015"		Buzzes/buzz_28.wav
WCreate 1024 "(x<4)+(x>55)&&(x<75)+(x>80)*0.015"		Buzzes/buzz_29.wav
WCreate 1024 "(x<3)+(x>17)&&(x<19)+(x>80)*0.015"		Buzzes/buzz_30.wav
WCreate 1024 "(x<3)+(x>19)&&(x<22)+(x>80)*0.015"		Buzzes/buzz_31.wav
WCreate 1024 "(x<3)+(x>21)&&(x<25)+(x>80)*0.015"		Buzzes/buzz_32.wav
WCreate 1024 "(x<3)+(x>23)&&(x<28)+(x>80)*0.015"		Buzzes/buzz_33.wav
WCreate 1024 "(x<3)+(x>25)&&(x<31)+(x>80)*0.015"		Buzzes/buzz_34.wav
WCreate 1024 "(x<3)+(x>27)&&(x<34)+(x>80)*0.015"		Buzzes/buzz_35.wav
WCreate 1024 "(x<3)+(x>29)&&(x<37)+(x>80)*0.015"		Buzzes/buzz_36.wav
WCreate 1024 "(x<3)+(x>31)&&(x<40)+(x>80)*0.015"		Buzzes/buzz_37.wav
WCreate 1024 "(x<3)+(x>33)&&(x<43)+(x>80)*0.015"		Buzzes/buzz_38.wav
WCreate 1024 "(x<3)+(x>35)&&(x<45)+(x>80)*0.015"		Buzzes/buzz_39.wav
WCreate 1024 "(x<3)+(x>37)&&(x<48)+(x>80)*0.015"		Buzzes/buzz_40.wav
WCreate 1024 "(x<3)+(x>39)&&(x<51)+(x>90)*0.015"		Buzzes/buzz_41.wav
WCreate 1024 "(x<3)+(x>41)&&(x<54)+(x>90)*0.015"		Buzzes/buzz_42.wav
WCreate 1024 "(x<3)+(x>43)&&(x<57)+(x>90)*0.015"		Buzzes/buzz_43.wav
WCreate 1024 "(x<3)+(x>45)&&(x<60)+(x>90)*0.015"		Buzzes/buzz_44.wav
WCreate 1024 "(x<3)+(x>47)&&(x<63)+(x>90)*0.015"		Buzzes/buzz_45.wav
WCreate 1024 "(x<3)+(x>49)&&(x<66)+(x>90)*0.015"		Buzzes/buzz_46.wav
WCreate 1024 "(x<3)+(x>51)&&(x<69)+(x>90)*0.015"		Buzzes/buzz_47.wav
WCreate 1024 "(x<3)+(x>53)&&(x<72)+(x>90)*0.015"		Buzzes/buzz_48.wav
WCreate 1024 "(x<3)+(x>55)&&(x<75)+(x>90)*0.015"		Buzzes/buzz_49.wav
WCreate 1024 "(x<9)+(x>17)&&(x<19)+(x>40)&&(x<80)"		Buzzes/buzz_50.wav
WCreate 1024 "(x<9)+(x>19)&&(x<22)+(x>40)&&(x<80)"		Buzzes/buzz_51.wav
WCreate 1024 "(x<9)+(x>21)&&(x<25)+(x>40)&&(x<80)"		Buzzes/buzz_52.wav
WCreate 1024 "(x<9)+(x>23)&&(x<28)+(x>40)&&(x<80)"		Buzzes/buzz_53.wav
WCreate 1024 "(x<9)+(x>25)&&(x<31)+(x>40)&&(x<80)"		Buzzes/buzz_54.wav
WCreate 1024 "(x<9)+(x>27)&&(x<34)+(x>40)&&(x<80)"		Buzzes/buzz_55.wav
WCreate 1024 "(x<9)+(x>29)&&(x<37)+(x>40)&&(x<80)"		Buzzes/buzz_56.wav
WCreate 1024 "(x<9)+(x>31)&&(x<40)+(x>40)&&(x<80)"		Buzzes/buzz_57.wav
WCreate 1024 "(x<9)+(x>33)&&(x<43)+(x>40)&&(x<80)"		Buzzes/buzz_58.wav
WCreate 1024 "(x<8)+(x>35)&&(x<45)+(x>40)&&(x<80)"		Buzzes/buzz_59.wav
WCreate 1024 "(x<8)+(x>17)&&(x<19)+(x>50)&&(x<80)"		Buzzes/buzz_60.wav
WCreate 1024 "(x<8)+(x>19)&&(x<22)+(x>50)&&(x<80)"		Buzzes/buzz_61.wav
WCreate 1024 "(x<8)+(x>21)&&(x<25)+(x>50)&&(x<80)"		Buzzes/buzz_62.wav
WCreate 1024 "(x<8)+(x>23)&&(x<28)+(x>50)&&(x<80)"		Buzzes/buzz_63.wav
WCreate 1024 "(x<8)+(x>25)&&(x<31)+(x>50)&&(x<80)"		Buzzes/buzz_64.wav
WCreate 1024 "(x<8)+(x>27)&&(x<34)+(x>50)&&(x<80)"		Buzzes/buzz_65.wav
WCreate 1024 "(x<8)+(x>29)&&(x<37)+(x>50)&&(x<80)"		Buzzes/buzz_66.wav
WCreate 1024 "(x<8)+(x>31)&&(x<40)+(x>50)&&(x<80)"		Buzzes/buzz_67.wav
WCreate 1024 "(x<8)+(x>33)&&(x<43)+(x>50)&&(x<80)"		Buzzes/buzz_68.wav
WCreate 1024 "(x<8)+(x>35)&&(x<45)+(x>50)&&(x<80)"		Buzzes/buzz_69.wav
WCreate 1024 "(x<8)+(x>37)&&(x<48)+(x>50)&&(x<80)"		Buzzes/buzz_70.wav
WCreate 1024 "(x<8)+(x>39)&&(x<51)+(x>60)&&(x<80)"		Buzzes/buzz_71.wav
WCreate 1024 "(x<8)+(x>41)&&(x<54)+(x>60)&&(x<80)"		Buzzes/buzz_72.wav
WCreate 1024 "(x<8)+(x>43)&&(x<57)+(x>60)&&(x<80)"		Buzzes/buzz_73.wav
WCreate 1024 "(x<8)+(x>45)&&(x<60)+(x>60)&&(x<80)"		Buzzes/buzz_74.wav
WCreate 1024 "(x<8)+(x>47)&&(x<63)+(x>60)&&(x<80)"		Buzzes/buzz_75.wav
WCreate 1024 "(x<8)+(x>49)&&(x<66)+(x>60)&&(x<80)"		Buzzes/buzz_76.wav
WCreate 1024 "(x<8)+(x>51)&&(x<69)+(x>60)&&(x<80)"		Buzzes/buzz_77.wav
WCreate 1024 "(x<8)+(x>53)&&(x<72)+(x>60)&&(x<80)"		Buzzes/buzz_78.wav
WCreate 1024 "(x<8)+(x>55)&&(x<75)+(x>60)&&(x<80)"		Buzzes/buzz_79.wav
WCreate 1024 "(x<7)+(x>17)&&(x<19)+(x>60)&&(x<80)"		Buzzes/buzz_80.wav
WCreate 1024 "(x<7)+(x>19)&&(x<22)+(x>60)&&(x<80)"		Buzzes/buzz_81.wav
WCreate 1024 "(x<7)+(x>21)&&(x<25)+(x>60)&&(x<80)"		Buzzes/buzz_82.wav
WCreate 1024 "(x<7)+(x>23)&&(x<28)+(x>60)&&(x<80)"		Buzzes/buzz_83.wav
WCreate 1024 "(x<7)+(x>25)&&(x<31)+(x>60)&&(x<80)"		Buzzes/buzz_84.wav
WCreate 1024 "(x<7)+(x>27)&&(x<34)+(x>60)&&(x<80)"		Buzzes/buzz_85.wav
WCreate 1024 "(x<7)+(x>29)&&(x<37)+(x>60)&&(x<80)"		Buzzes/buzz_86.wav
WCreate 1024 "(x<7)+(x>31)&&(x<40)+(x>60)&&(x<80)"		Buzzes/buzz_87.wav
WCreate 1024 "(x<7)+(x>33)&&(x<43)+(x>60)&&(x<80)"		Buzzes/buzz_88.wav
WCreate 1024 "(x<7)+(x>35)&&(x<45)+(x>60)&&(x<80)"		Buzzes/buzz_89.wav
WCreate 1024 "(x<7)+(x>37)&&(x<48)+(x>60)&&(x<80)"		Buzzes/buzz_90.wav
WCreate 1024 "(x<7)+(x>39)&&(x<51)+(x>70)&&(x<80)"		Buzzes/buzz_91.wav
WCreate 1024 "(x<7)+(x>41)&&(x<54)+(x>70)&&(x<80)"		Buzzes/buzz_92.wav
WCreate 1024 "(x<7)+(x>43)&&(x<57)+(x>70)&&(x<80)"		Buzzes/buzz_93.wav
WCreate 1024 "(x<7)+(x>45)&&(x<60)+(x>70)&&(x<80)"		Buzzes/buzz_94.wav
WCreate 1024 "(x<7)+(x>47)&&(x<63)+(x>70)&&(x<80)"		Buzzes/buzz_95.wav
WCreate 1024 "(x<7)+(x>49)&&(x<66)+(x>70)&&(x<80)"		Buzzes/buzz_96.wav
WCreate 1024 "(x<7)+(x>51)&&(x<69)+(x>70)&&(x<80)"		Buzzes/buzz_97.wav
WCreate 1024 "(x<7)+(x>53)&&(x<72)+(x>70)&&(x<80)"		Buzzes/buzz_98.wav
WCreate 1024 "(x<7)+(x>55)&&(x<75)+(x>70)&&(x<80)"		Buzzes/buzz_99.wav

mkdir -p Buzzes_Filtered
WCreate 1024 "(x<6)+((x>17)&&(x<19))*0.5"		Buzzes_Filtered/buzz_00.wav
WCreate 1024 "(x<6)+((x>19)&&(x<22))*0.5"		Buzzes_Filtered/buzz_01.wav
WCreate 1024 "(x<6)+((x>21)&&(x<25))*0.5"		Buzzes_Filtered/buzz_02.wav
WCreate 1024 "(x<6)+((x>23)&&(x<28))*0.5"		Buzzes_Filtered/buzz_03.wav
WCreate 1024 "(x<6)+((x>25)&&(x<31))*0.5"		Buzzes_Filtered/buzz_04.wav
WCreate 1024 "(x<6)+((x>27)&&(x<34))*0.5"		Buzzes_Filtered/buzz_05.wav
WCreate 1024 "(x<6)+((x>29)&&(x<37))*0.5"		Buzzes_Filtered/buzz_06.wav
WCreate 1024 "(x<6)+((x>31)&&(x<40))*0.5"		Buzzes_Filtered/buzz_07.wav
WCreate 1024 "(x<6)+((x>33)&&(x<43))*0.5"		Buzzes_Filtered/buzz_08.wav
WCreate 1024 "(x<4)+((x>35)&&(x<45))*0.5"		Buzzes_Filtered/buzz_09.wav
WCreate 1024 "(x<4)+((x>17)&&(x<19))*0.5"		Buzzes_Filtered/buzz_10.wav
WCreate 1024 "(x<4)+((x>19)&&(x<22))*0.5"		Buzzes_Filtered/buzz_11.wav
WCreate 1024 "(x<4)+((x>21)&&(x<25))*0.5"		Buzzes_Filtered/buzz_12.wav
WCreate 1024 "(x<4)+((x>23)&&(x<28))*0.5"		Buzzes_Filtered/buzz_13.wav
WCreate 1024 "(x<4)+((x>25)&&(x<31))*0.5"		Buzzes_Filtered/buzz_14.wav
WCreate 1024 "(x<4)+((x>27)&&(x<34))*0.5"		Buzzes_Filtered/buzz_15.wav
WCreate 1024 "(x<4)+((x>29)&&(x<37))*0.5"		Buzzes_Filtered/buzz_16.wav
WCreate 1024 "(x<4)+((x>31)&&(x<40))*0.5"		Buzzes_Filtered/buzz_17.wav
WCreate 1024 "(x<4)+((x>33)&&(x<43))*0.5"		Buzzes_Filtered/buzz_18.wav
WCreate 1024 "(x<4)+((x>35)&&(x<45))*0.5"		Buzzes_Filtered/buzz_19.wav
WCreate 1024 "(x<4)+((x>37)&&(x<48))*0.5"		Buzzes_Filtered/buzz_20.wav
WCreate 1024 "(x<4)+((x>39)&&(x<51))*0.5"		Buzzes_Filtered/buzz_21.wav
WCreate 1024 "(x<4)+((x>41)&&(x<54))*0.5"		Buzzes_Filtered/buzz_22.wav
WCreate 1024 "(x<4)+((x>43)&&(x<57))*0.5"		Buzzes_Filtered/buzz_23.wav
WCreate 1024 "(x<4)+((x>45)&&(x<60))*0.5"		Buzzes_Filtered/buzz_24.wav
WCreate 1024 "(x<4)+((x>47)&&(x<63))*0.5"		Buzzes_Filtered/buzz_25.wav
WCreate 1024 "(x<4)+((x>49)&&(x<66))*0.5"		Buzzes_Filtered/buzz_26.wav
WCreate 1024 "(x<4)+((x>51)&&(x<69))*0.5"		Buzzes_Filtered/buzz_27.wav
WCreate 1024 "(x<4)+((x>53)&&(x<72))*0.5"		Buzzes_Filtered/buzz_28.wav
WCreate 1024 "(x<4)+((x>55)&&(x<75))*0.5"		Buzzes_Filtered/buzz_29.wav
WCreate 1024 "(x<3)+((x>17)&&(x<19))*0.5"		Buzzes_Filtered/buzz_30.wav
WCreate 1024 "(x<3)+((x>19)&&(x<22))*0.5"		Buzzes_Filtered/buzz_31.wav
WCreate 1024 "(x<3)+((x>21)&&(x<25))*0.5"		Buzzes_Filtered/buzz_32.wav
WCreate 1024 "(x<3)+((x>23)&&(x<28))*0.5"		Buzzes_Filtered/buzz_33.wav
WCreate 1024 "(x<3)+((x>25)&&(x<31))*0.5"		Buzzes_Filtered/buzz_34.wav
WCreate 1024 "(x<3)+((x>27)&&(x<34))*0.5"		Buzzes_Filtered/buzz_35.wav
WCreate 1024 "(x<3)+((x>29)&&(x<37))*0.5"		Buzzes_Filtered/buzz_36.wav
WCreate 1024 "(x<3)+((x>31)&&(x<40))*0.5"		Buzzes_Filtered/buzz_37.wav
WCreate 1024 "(x<3)+((x>33)&&(x<43))*0.5"		Buzzes_Filtered/buzz_38.wav
WCreate 1024 "(x<3)+((x>35)&&(x<45))*0.5"		Buzzes_Filtered/buzz_39.wav
WCreate 1024 "(x<3)+((x>37)&&(x<48))*0.5"		Buzzes_Filtered/buzz_40.wav
WCreate 1024 "(x<3)+((x>39)&&(x<51))*0.5"		Buzzes_Filtered/buzz_41.wav
WCreate 1024 "(x<3)+((x>41)&&(x<54))*0.5"		Buzzes_Filtered/buzz_42.wav
WCreate 1024 "(x<3)+((x>43)&&(x<57))*0.5"		Buzzes_Filtered/buzz_43.wav
WCreate 1024 "(x<3)+((x>45)&&(x<60))*0.5"		Buzzes_Filtered/buzz_44.wav
WCreate 1024 "(x<3)+((x>47)&&(x<63))*0.5"		Buzzes_Filtered/buzz_45.wav
WCreate 1024 "(x<3)+((x>49)&&(x<66))*0.5"		Buzzes_Filtered/buzz_46.wav
WCreate 1024 "(x<3)+((x>51)&&(x<69))*0.5"		Buzzes_Filtered/buzz_47.wav
WCreate 1024 "(x<3)+((x>53)&&(x<72))*0.5"		Buzzes_Filtered/buzz_48.wav
WCreate 1024 "(x<3)+((x>55)&&(x<75))*0.5"		Buzzes_Filtered/buzz_49.wav
WCreate 1024 "(x<9)+((x>17)&&(x<19))*0.5"		Buzzes_Filtered/buzz_50.wav
WCreate 1024 "(x<9)+((x>19)&&(x<22))*0.5"		Buzzes_Filtered/buzz_51.wav
WCreate 1024 "(x<9)+((x>21)&&(x<25))*0.5"		Buzzes_Filtered/buzz_52.wav
WCreate 1024 "(x<9)+((x>23)&&(x<28))*0.5"		Buzzes_Filtered/buzz_53.wav
WCreate 1024 "(x<9)+((x>25)&&(x<31))*0.5"		Buzzes_Filtered/buzz_54.wav
WCreate 1024 "(x<9)+((x>27)&&(x<34))*0.5"		Buzzes_Filtered/buzz_55.wav
WCreate 1024 "(x<9)+((x>29)&&(x<37))*0.5"		Buzzes_Filtered/buzz_56.wav
WCreate 1024 "(x<9)+((x>31)&&(x<40))*0.5"		Buzzes_Filtered/buzz_57.wav
WCreate 1024 "(x<9)+((x>33)&&(x<43))*0.5"		Buzzes_Filtered/buzz_58.wav
WCreate 1024 "(x<8)+((x>35)&&(x<45))*0.5"		Buzzes_Filtered/buzz_59.wav
WCreate 1024 "(x<8)+((x>17)&&(x<19))*0.5"		Buzzes_Filtered/buzz_60.wav
WCreate 1024 "(x<8)+((x>19)&&(x<22))*0.5"		Buzzes_Filtered/buzz_61.wav
WCreate 1024 "(x<8)+((x>21)&&(x<25))*0.5"		Buzzes_Filtered/buzz_62.wav
WCreate 1024 "(x<8)+((x>23)&&(x<28))*0.5"		Buzzes_Filtered/buzz_63.wav
WCreate 1024 "(x<8)+((x>25)&&(x<31))*0.5"		Buzzes_Filtered/buzz_64.wav
WCreate 1024 "(x<8)+((x>27)&&(x<34))*0.5"		Buzzes_Filtered/buzz_65.wav
WCreate 1024 "(x<8)+((x>29)&&(x<37))*0.5"		Buzzes_Filtered/buzz_66.wav
WCreate 1024 "(x<8)+((x>31)&&(x<40))*0.5"		Buzzes_Filtered/buzz_67.wav
WCreate 1024 "(x<8)+((x>33)&&(x<43))*0.5"		Buzzes_Filtered/buzz_68.wav
WCreate 1024 "(x<8)+((x>35)&&(x<45))*0.5"		Buzzes_Filtered/buzz_69.wav
WCreate 1024 "(x<8)+((x>37)&&(x<48))*0.5"		Buzzes_Filtered/buzz_70.wav
WCreate 1024 "(x<8)+((x>39)&&(x<51))*0.5"		Buzzes_Filtered/buzz_71.wav
WCreate 1024 "(x<8)+((x>41)&&(x<54))*0.5"		Buzzes_Filtered/buzz_72.wav
WCreate 1024 "(x<8)+((x>43)&&(x<57))*0.5"		Buzzes_Filtered/buzz_73.wav
WCreate 1024 "(x<8)+((x>45)&&(x<60))*0.5"		Buzzes_Filtered/buzz_74.wav
WCreate 1024 "(x<8)+((x>47)&&(x<63))*0.5"		Buzzes_Filtered/buzz_75.wav
WCreate 1024 "(x<8)+((x>49)&&(x<66))*0.5"		Buzzes_Filtered/buzz_76.wav
WCreate 1024 "(x<8)+((x>51)&&(x<69))*0.5"		Buzzes_Filtered/buzz_77.wav
WCreate 1024 "(x<8)+((x>53)&&(x<72))*0.5"		Buzzes_Filtered/buzz_78.wav
WCreate 1024 "(x<8)+((x>55)&&(x<75))*0.5"		Buzzes_Filtered/buzz_79.wav
WCreate 1024 "(x<7)+((x>17)&&(x<19))*0.5"		Buzzes_Filtered/buzz_80.wav
WCreate 1024 "(x<7)+((x>19)&&(x<22))*0.5"		Buzzes_Filtered/buzz_81.wav
WCreate 1024 "(x<7)+((x>21)&&(x<25))*0.5"		Buzzes_Filtered/buzz_82.wav
WCreate 1024 "(x<7)+((x>23)&&(x<28))*0.5"		Buzzes_Filtered/buzz_83.wav
WCreate 1024 "(x<7)+((x>25)&&(x<31))*0.5"		Buzzes_Filtered/buzz_84.wav
WCreate 1024 "(x<7)+((x>27)&&(x<34))*0.5"		Buzzes_Filtered/buzz_85.wav
WCreate 1024 "(x<7)+((x>29)&&(x<37))*0.5"		Buzzes_Filtered/buzz_86.wav
WCreate 1024 "(x<7)+((x>31)&&(x<40))*0.5"		Buzzes_Filtered/buzz_87.wav
WCreate 1024 "(x<7)+((x>33)&&(x<43))*0.5"		Buzzes_Filtered/buzz_88.wav
WCreate 1024 "(x<7)+((x>35)&&(x<45))*0.5"		Buzzes_Filtered/buzz_89.wav
WCreate 1024 "(x<7)+((x>37)&&(x<48))*0.5"		Buzzes_Filtered/buzz_90.wav
WCreate 1024 "(x<7)+((x>39)&&(x<51))*0.5"		Buzzes_Filtered/buzz_91.wav
WCreate 1024 "(x<7)+((x>41)&&(x<54))*0.5"		Buzzes_Filtered/buzz_92.wav
WCreate 1024 "(x<7)+((x>43)&&(x<57))*0.5"		Buzzes_Filtered/buzz_93.wav
WCreate 1024 "(x<7)+((x>45)&&(x<60))*0.5"		Buzzes_Filtered/buzz_94.wav
WCreate 1024 "(x<7)+((x>47)&&(x<63))*0.5"		Buzzes_Filtered/buzz_95.wav
WCreate 1024 "(x<7)+((x>49)&&(x<66))*0.5"		Buzzes_Filtered/buzz_96.wav
WCreate 1024 "(x<7)+((x>51)&&(x<69))*0.5"		Buzzes_Filtered/buzz_97.wav
WCreate 1024 "(x<7)+((x>53)&&(x<72))*0.5"		Buzzes_Filtered/buzz_98.wav
WCreate 1024 "(x<7)+((x>55)&&(x<75))*0.5"		Buzzes_Filtered/buzz_99.wav

mkdir -p Even_Partials

WCreate 1024 "1,1,0,1" 								Even_Partials/even_2_4.wav
WCreate 1024 "1,1,0,0.75" 							Even_Partials/even_2_4a.wav
WCreate 1024 "1,1,0,0.5" 							Even_Partials/even_2_4b.wav
WCreate 1024 "1,1,0,0.25" 							Even_Partials/even_2_4c.wav
WCreate 1024 "1,1,0,1,0,1" 							Even_Partials/even_2_4_6.wav
WCreate 1024 "1,1,0,1,0,0.75" 						Even_Partials/even_2_4_6a.wav
WCreate 1024 "1,1,0,1,0,0.5" 						Even_Partials/even_2_4_6b.wav
WCreate 1024 "1,1,0,1,0,0.25" 						Even_Partials/even_2_4_6c.wav
WCreate 1024 "1,1,0,1,0,1,0,1" 						Even_Partials/even_2_4_6_8.wav
WCreate 1024 "1,1,0,1,0,1,0,0.75" 					Even_Partials/even_2_4_6_8a.wav
WCreate 1024 "1,1,0,1,0,1,0,0.5" 					Even_Partials/even_2_4_6_8b.wav
WCreate 1024 "1,1,0,1,0,1,0,0.25" 					Even_Partials/even_2_4_6_8c.wav
WCreate 1024 "1,1,0,1,0,1,0,1,0,1" 					Even_Partials/even_2_4_6_8_10.wav
WCreate 1024 "1,1,0,1,0,1,0,1,0,0.75" 				Even_Partials/even_2_4_6_8_10a.wav
WCreate 1024 "1,1,0,1,0,1,0,1,0,0.5" 				Even_Partials/even_2_4_6_8_10b.wav
WCreate 1024 "1,1,0,1,0,1,0,1,0,0.25" 				Even_Partials/even_2_4_6_8_10c.wav
WCreate 1024 "(x%2=0)&&(x<=10)+(x=12)*1" 			Even_Partials/even_2_4_6_8_10_12.wav
WCreate 1024 "(x%2=0)&&(x<=10)+(x=12)*0.75" 		Even_Partials/even_2_4_6_8_10_12a.wav
WCreate 1024 "(x%2=0)&&(x<=10)+(x=12)*0.5" 		Even_Partials/even_2_4_6_8_10_12b.wav
WCreate 1024 "(x%2=0)&&(x<=10)+(x=12)*0.25" 		Even_Partials/even_2_4_6_8_10_12c.wav
WCreate 1024 "(x%2=0)&&(x<=12)+(x=14)*1" 			Even_Partials/even_2_4_6_8_10_12_14.wav
WCreate 1024 "(x%2=0)&&(x<=12)+(x=14)*0.75" 		Even_Partials/even_2_4_6_8_10_12_14a.wav
WCreate 1024 "(x%2=0)&&(x<=12)+(x=14)*0.5" 		Even_Partials/even_2_4_6_8_10_12_14b.wav
WCreate 1024 "(x%2=0)&&(x<=12)+(x=14)*0.25" 		Even_Partials/even_2_4_6_8_10_12_14c.wav
WCreate 1024 "(x%2=0)&&(x<=14)+(x=16)*1" 			Even_Partials/even_2_4_6_8_10_12_14_16.wav
WCreate 1024 "(x%2=0)&&(x<=14)+(x=16)*0.75" 		Even_Partials/even_2_4_6_8_10_12_14_16a.wav
WCreate 1024 "(x%2=0)&&(x<=14)+(x=16)*0.5" 		Even_Partials/even_2_4_6_8_10_12_14_16b.wav
WCreate 1024 "(x%2=0)&&(x<=14)+(x=16)*0.25" 		Even_Partials/even_2_4_6_8_10_12_14_16c.wav
WCreate 1024 "(x%2=0)&&(x<=16)+(x=18)*1" 			Even_Partials/even_2_4_6_8_10_12_14_16_18.wav
WCreate 1024 "(x%2=0)&&(x<=16)+(x=18)*0.75" 		Even_Partials/even_2_4_6_8_10_12_14_16_18a.wav
WCreate 1024 "(x%2=0)&&(x<=16)+(x=18)*0.5" 		Even_Partials/even_2_4_6_8_10_12_14_16_18b.wav
WCreate 1024 "(x%2=0)&&(x<=16)+(x=18)*0.25" 		Even_Partials/even_2_4_6_8_10_12_14_16_18c.wav
WCreate 1024 "(x%2=0)&&(x<=18)+(x=20)*1" 			Even_Partials/even_2_4_6_8_10_12_14_16_18_20.wav
WCreate 1024 "(x%2=0)&&(x<=18)+(x=20)*0.75" 		Even_Partials/even_2_4_6_8_10_12_14_16_18_20a.wav
WCreate 1024 "(x%2=0)&&(x<=18)+(x=20)*0.5" 		Even_Partials/even_2_4_6_8_10_12_14_16_18_20b.wav
WCreate 1024 "(x%2=0)&&(x<=18)+(x=20)*0.25" 		Even_Partials/even_2_4_6_8_10_12_14_16_18_20c.wav

mkdir -p Odd_Partials
WCreate 1024 "(x%2=1)&&(x<=3)+(x=5)*1" 			Odd_Partials/odd_3_5.wav
WCreate 1024 "(x%2=1)&&(x<=3)+(x=5)*0.75"	 		Odd_Partials/odd_3_5a.wav
WCreate 1024 "(x%2=1)&&(x<=3)+(x=5)*0.5" 			Odd_Partials/odd_3_5b.wav
WCreate 1024 "(x%2=1)&&(x<=3)+(x=5)*0.25" 			Odd_Partials/odd_3_5c.wav
WCreate 1024 "(x%2=1)&&(x<=5)+(x=7)*1" 			Odd_Partials/odd_3_5_7.wav
WCreate 1024 "(x%2=1)&&(x<=5)+(x=7)*0.75"	 		Odd_Partials/odd_3_5_7a.wav
WCreate 1024 "(x%2=1)&&(x<=5)+(x=7)*0.5" 			Odd_Partials/odd_3_5_7b.wav
WCreate 1024 "(x%2=1)&&(x<=5)+(x=7)*0.25" 			Odd_Partials/odd_3_5_7c.wav
WCreate 1024 "(x%2=1)&&(x<=7)+(x=9)*1" 			Odd_Partials/odd_3_5_7_9.wav
WCreate 1024 "(x%2=1)&&(x<=7)+(x=9)*0.75"	 		Odd_Partials/odd_3_5_7_9a.wav
WCreate 1024 "(x%2=1)&&(x<=7)+(x=9)*0.5" 			Odd_Partials/odd_3_5_7_9b.wav
WCreate 1024 "(x%2=1)&&(x<=7)+(x=9)*0.25" 			Odd_Partials/odd_3_5_7_9c.wav
WCreate 1024 "(x%2=1)&&(x<=9)+(x=11)*1" 			Odd_Partials/odd_3_5_7_9_11.wav
WCreate 1024 "(x%2=1)&&(x<=9)+(x=11)*0.75" 		Odd_Partials/odd_3_5_7_9_11a.wav
WCreate 1024 "(x%2=1)&&(x<=9)+(x=11)*0.5" 			Odd_Partials/odd_3_5_7_9_11b.wav
WCreate 1024 "(x%2=1)&&(x<=9)+(x=11)*0.25" 		Odd_Partials/odd_3_5_7_9_11c.wav
WCreate 1024 "(x%2=1)&&(x<=11)+(x=13)*1" 			Odd_Partials/odd_3_5_7_9_11_13.wav
WCreate 1024 "(x%2=1)&&(x<=11)+(x=13)*0.75" 		Odd_Partials/odd_3_5_7_9_11_13a.wav
WCreate 1024 "(x%2=1)&&(x<=11)+(x=13)*0.5" 		Odd_Partials/odd_3_5_7_9_11_13b.wav
WCreate 1024 "(x%2=1)&&(x<=11)+(x=13)*0.25" 		Odd_Partials/odd_3_5_7_9_11_13c.wav
WCreate 1024 "(x%2=1)&&(x<=13)+(x=15)*1" 			Odd_Partials/odd_3_5_7_9_11_13_15.wav
WCreate 1024 "(x%2=1)&&(x<=13)+(x=15)*0.75" 		Odd_Partials/odd_3_5_7_9_11_13_15a.wav
WCreate 1024 "(x%2=1)&&(x<=13)+(x=15)*0.5" 		Odd_Partials/odd_3_5_7_9_11_13_15b.wav
WCreate 1024 "(x%2=1)&&(x<=13)+(x=15)*0.25" 		Odd_Partials/odd_3_5_7_9_11_13_15c.wav
WCreate 1024 "(x%2=1)&&(x<=15)+(x=17)*1" 			Odd_Partials/odd_3_5_7_9_11_13_15_17.wav
WCreate 1024 "(x%2=1)&&(x<=15)+(x=17)*0.75" 		Odd_Partials/odd_3_5_7_9_11_13_15_17a.wav
WCreate 1024 "(x%2=1)&&(x<=15)+(x=17)*0.5" 		Odd_Partials/odd_3_5_7_9_11_13_15_17b.wav
WCreate 1024 "(x%2=1)&&(x<=15)+(x=17)*0.25" 		Odd_Partials/odd_3_5_7_9_11_13_15_17c.wav

mkdir -p Noisy
WCreate 1024 "(x=1)-(x=29)*0.2+(x=41)*0.2"		Noisy/noisy_00.wav
WCreate 1024 "(x=1)-(x=30)*0.2+(x=42)*0.2"		Noisy/noisy_01.wav
WCreate 1024 "(x=1)-(x=31)*0.2+(x=43)*0.2"		Noisy/noisy_02.wav
WCreate 1024 "(x=1)-(x=32)*0.2+(x=44)*0.2"		Noisy/noisy_03.wav
WCreate 1024 "(x=1)-(x=33)*0.2+(x=45)*0.2"		Noisy/noisy_04.wav
WCreate 1024 "(x=1)-(x=34)*0.2+(x=46)*0.2"		Noisy/noisy_05.wav
WCreate 1024 "(x=1)-(x=35)*0.2+(x=47)*0.2"		Noisy/noisy_06.wav
WCreate 1024 "(x=1)-(x=36)*0.2+(x=48)*0.2"		Noisy/noisy_07.wav
WCreate 1024 "(x=1)-(x=37)*0.2+(x=49)*0.2"		Noisy/noisy_08.wav
WCreate 1024 "(x=1)-(x=38)*0.2+(x=50)*0.2"		Noisy/noisy_09.wav
WCreate 1024 "(x=1)-(x=39)*0.2+(x=51)*0.2"		Noisy/noisy_10.wav
WCreate 1024 "(x=1)-(x=40)*0.2+(x=52)*0.2"		Noisy/noisy_11.wav
WCreate 1024 "(x=1)-(x=41)*0.2+(x=53)*0.2"		Noisy/noisy_12.wav
WCreate 1024 "(x=1)-(x=42)*0.2+(x=54)*0.2"		Noisy/noisy_13.wav
WCreate 1024 "(x=1)-(x=43)*0.2+(x=55)*0.2"		Noisy/noisy_14.wav
WCreate 1024 "(x=1)-(x=44)*0.2+(x=56)*0.2"		Noisy/noisy_15.wav
WCreate 1024 "(x=1)-(x=45)*0.2+(x=57)*0.2"		Noisy/noisy_16.wav
WCreate 1024 "(x=1)-(x=46)*0.2+(x=58)*0.2"		Noisy/noisy_17.wav
WCreate 1024 "(x=1)-(x=47)*0.2+(x=59)*0.2"		Noisy/noisy_18.wav
WCreate 1024 "(x=1)-(x=48)*0.2+(x=60)*0.2"		Noisy/noisy_19.wav
WCreate 1024 "(x=1)-(x=49)*0.2+(x=61)*0.2"		Noisy/noisy_20.wav

mkdir -p Numeric
WCreate 1024 "(x<3)*#"	Numeric/Numeric_000.wav -seed 0
WCreate 1024 "(x<3)*#"	Numeric/Numeric_001.wav -seed 1
WCreate 1024 "(x<3)*#"	Numeric/Numeric_002.wav -seed 2
WCreate 1024 "(x<3)*#"	Numeric/Numeric_003.wav -seed 3
WCreate 1024 "(x<3)*#"	Numeric/Numeric_004.wav -seed 4
WCreate 1024 "(x<3)*#"	Numeric/Numeric_005.wav -seed 5
WCreate 1024 "(x<3)*#"	Numeric/Numeric_006.wav -seed 6
WCreate 1024 "(x<3)*#"	Numeric/Numeric_007.wav -seed 7
WCreate 1024 "(x<3)*#"	Numeric/Numeric_008.wav -seed 8
WCreate 1024 "(x<3)*#"	Numeric/Numeric_009.wav -seed 9
WCreate 1024 "(x<5)*#"	Numeric/Numeric_010.wav -seed 0
WCreate 1024 "(x<5)*#"	Numeric/Numeric_011.wav -seed 1
WCreate 1024 "(x<5)*#"	Numeric/Numeric_012.wav -seed 2
WCreate 1024 "(x<5)*#"	Numeric/Numeric_013.wav -seed 3
WCreate 1024 "(x<5)*#"	Numeric/Numeric_014.wav -seed 4
WCreate 1024 "(x<5)*#"	Numeric/Numeric_015.wav -seed 5
WCreate 1024 "(x<5)*#"	Numeric/Numeric_016.wav -seed 6
WCreate 1024 "(x<5)*#"	Numeric/Numeric_017.wav -seed 7
WCreate 1024 "(x<5)*#"	Numeric/Numeric_018.wav -seed 8
WCreate 1024 "(x<5)*#"	Numeric/Numeric_019.wav -seed 9
WCreate 1024 "(x<8)*#"	Numeric/Numeric_020.wav -seed 0
WCreate 1024 "(x<8)*#"	Numeric/Numeric_021.wav -seed 1
WCreate 1024 "(x<8)*#"	Numeric/Numeric_022.wav -seed 2
WCreate 1024 "(x<8)*#"	Numeric/Numeric_023.wav -seed 3
WCreate 1024 "(x<8)*#"	Numeric/Numeric_024.wav -seed 4
WCreate 1024 "(x<8)*#"	Numeric/Numeric_025.wav -seed 5
WCreate 1024 "(x<8)*#"	Numeric/Numeric_026.wav -seed 6
WCreate 1024 "(x<8)*#"	Numeric/Numeric_027.wav -seed 7
WCreate 1024 "(x<8)*#"	Numeric/Numeric_028.wav -seed 8
WCreate 1024 "(x<8)*#"	Numeric/Numeric_029.wav -seed 9
WCreate 1024 "(x<12)*#"	Numeric/Numeric_030.wav -seed 0
WCreate 1024 "(x<12)*#"	Numeric/Numeric_031.wav -seed 1
WCreate 1024 "(x<12)*#"	Numeric/Numeric_032.wav -seed 2
WCreate 1024 "(x<12)*#"	Numeric/Numeric_033.wav -seed 3
WCreate 1024 "(x<12)*#"	Numeric/Numeric_034.wav -seed 4
WCreate 1024 "(x<12)*#"	Numeric/Numeric_035.wav -seed 5
WCreate 1024 "(x<12)*#"	Numeric/Numeric_036.wav -seed 6
WCreate 1024 "(x<12)*#"	Numeric/Numeric_037.wav -seed 7
WCreate 1024 "(x<12)*#"	Numeric/Numeric_038.wav -seed 8
WCreate 1024 "(x<12)*#"	Numeric/Numeric_039.wav -seed 9
WCreate 1024 "(x<16)*#"	Numeric/Numeric_040.wav -seed 0
WCreate 1024 "(x<16)*#"	Numeric/Numeric_041.wav -seed 1
WCreate 1024 "(x<16)*#"	Numeric/Numeric_042.wav -seed 2
WCreate 1024 "(x<16)*#"	Numeric/Numeric_043.wav -seed 3
WCreate 1024 "(x<16)*#"	Numeric/Numeric_044.wav -seed 4
WCreate 1024 "(x<16)*#"	Numeric/Numeric_045.wav -seed 5
WCreate 1024 "(x<16)*#"	Numeric/Numeric_046.wav -seed 6
WCreate 1024 "(x<16)*#"	Numeric/Numeric_047.wav -seed 7
WCreate 1024 "(x<16)*#"	Numeric/Numeric_048.wav -seed 8
WCreate 1024 "(x<16)*#"	Numeric/Numeric_049.wav -seed 9
WCreate 1024 "(x<19)*#"	Numeric/Numeric_050.wav -seed 0
WCreate 1024 "(x<19)*#"	Numeric/Numeric_051.wav -seed 1
WCreate 1024 "(x<19)*#"	Numeric/Numeric_052.wav -seed 2
WCreate 1024 "(x<19)*#"	Numeric/Numeric_053.wav -seed 3
WCreate 1024 "(x<19)*#"	Numeric/Numeric_054.wav -seed 4
WCreate 1024 "(x<19)*#"	Numeric/Numeric_055.wav -seed 5
WCreate 1024 "(x<19)*#"	Numeric/Numeric_056.wav -seed 6
WCreate 1024 "(x<19)*#"	Numeric/Numeric_057.wav -seed 7
WCreate 1024 "(x<19)*#"	Numeric/Numeric_058.wav -seed 8
WCreate 1024 "(x<19)*#"	Numeric/Numeric_059.wav -seed 9
WCreate 1024 "(x<23)*#"	Numeric/Numeric_060.wav -seed 0
WCreate 1024 "(x<23)*#"	Numeric/Numeric_061.wav -seed 1
WCreate 1024 "(x<23)*#"	Numeric/Numeric_062.wav -seed 2
WCreate 1024 "(x<23)*#"	Numeric/Numeric_063.wav -seed 3
WCreate 1024 "(x<23)*#"	Numeric/Numeric_064.wav -seed 4
WCreate 1024 "(x<23)*#"	Numeric/Numeric_065.wav -seed 5
WCreate 1024 "(x<23)*#"	Numeric/Numeric_066.wav -seed 6
WCreate 1024 "(x<23)*#"	Numeric/Numeric_067.wav -seed 7
WCreate 1024 "(x<23)*#"	Numeric/Numeric_068.wav -seed 8
WCreate 1024 "(x<23)*#"	Numeric/Numeric_069.wav -seed 9
WCreate 1024 "(x<27)*#"	Numeric/Numeric_070.wav -seed 0
WCreate 1024 "(x<27)*#"	Numeric/Numeric_071.wav -seed 1
WCreate 1024 "(x<27)*#"	Numeric/Numeric_072.wav -seed 2
WCreate 1024 "(x<27)*#"	Numeric/Numeric_073.wav -seed 3
WCreate 1024 "(x<27)*#"	Numeric/Numeric_074.wav -seed 4
WCreate 1024 "(x<27)*#"	Numeric/Numeric_075.wav -seed 5
WCreate 1024 "(x<27)*#"	Numeric/Numeric_076.wav -seed 6
WCreate 1024 "(x<27)*#"	Numeric/Numeric_077.wav -seed 7
WCreate 1024 "(x<27)*#"	Numeric/Numeric_078.wav -seed 8
WCreate 1024 "(x<27)*#"	Numeric/Numeric_079.wav -seed 9
WCreate 1024 "(x<31)*#"	Numeric/Numeric_080.wav -seed 0
WCreate 1024 "(x<31)*#"	Numeric/Numeric_081.wav -seed 1
WCreate 1024 "(x<31)*#"	Numeric/Numeric_082.wav -seed 2
WCreate 1024 "(x<31)*#"	Numeric/Numeric_083.wav -seed 3
WCreate 1024 "(x<31)*#"	Numeric/Numeric_084.wav -seed 4
WCreate 1024 "(x<31)*#"	Numeric/Numeric_085.wav -seed 5
WCreate 1024 "(x<31)*#"	Numeric/Numeric_086.wav -seed 6
WCreate 1024 "(x<31)*#"	Numeric/Numeric_087.wav -seed 7
WCreate 1024 "(x<31)*#"	Numeric/Numeric_088.wav -seed 8
WCreate 1024 "(x<31)*#"	Numeric/Numeric_089.wav -seed 9
WCreate 1024 "(x<35)*#"	Numeric/Numeric_090.wav -seed 0
WCreate 1024 "(x<35)*#"	Numeric/Numeric_091.wav -seed 1
WCreate 1024 "(x<35)*#"	Numeric/Numeric_092.wav -seed 2
WCreate 1024 "(x<35)*#"	Numeric/Numeric_093.wav -seed 3
WCreate 1024 "(x<35)*#"	Numeric/Numeric_094.wav -seed 4
WCreate 1024 "(x<35)*#"	Numeric/Numeric_095.wav -seed 5
WCreate 1024 "(x<35)*#"	Numeric/Numeric_096.wav -seed 6
WCreate 1024 "(x<35)*#"	Numeric/Numeric_097.wav -seed 7
WCreate 1024 "(x<35)*#"	Numeric/Numeric_098.wav -seed 8
WCreate 1024 "(x<35)*#"	Numeric/Numeric_099.wav -seed 9
WCreate 1024 "(x<39)*#"	Numeric/Numeric_100.wav -seed 0
WCreate 1024 "(x<39)*#"	Numeric/Numeric_101.wav -seed 1
WCreate 1024 "(x<39)*#"	Numeric/Numeric_102.wav -seed 2
WCreate 1024 "(x<39)*#"	Numeric/Numeric_103.wav -seed 3
WCreate 1024 "(x<39)*#"	Numeric/Numeric_104.wav -seed 4
WCreate 1024 "(x<39)*#"	Numeric/Numeric_105.wav -seed 5
WCreate 1024 "(x<39)*#"	Numeric/Numeric_106.wav -seed 6
WCreate 1024 "(x<39)*#"	Numeric/Numeric_107.wav -seed 7
WCreate 1024 "(x<39)*#"	Numeric/Numeric_108.wav -seed 8
WCreate 1024 "(x<39)*#"	Numeric/Numeric_109.wav -seed 9
WCreate 1024 "(x<45)*#"	Numeric/Numeric_110.wav -seed 0
WCreate 1024 "(x<45)*#"	Numeric/Numeric_111.wav -seed 1
WCreate 1024 "(x<45)*#"	Numeric/Numeric_112.wav -seed 2
WCreate 1024 "(x<45)*#"	Numeric/Numeric_113.wav -seed 3
WCreate 1024 "(x<45)*#"	Numeric/Numeric_114.wav -seed 4
WCreate 1024 "(x<45)*#"	Numeric/Numeric_115.wav -seed 5
WCreate 1024 "(x<45)*#"	Numeric/Numeric_116.wav -seed 6
WCreate 1024 "(x<45)*#"	Numeric/Numeric_117.wav -seed 7
WCreate 1024 "(x<45)*#"	Numeric/Numeric_118.wav -seed 8
WCreate 1024 "(x<45)*#"	Numeric/Numeric_119.wav -seed 9
WCreate 1024 "(x<51)*#"	Numeric/Numeric_120.wav -seed 0
WCreate 1024 "(x<51)*#"	Numeric/Numeric_121.wav -seed 1
WCreate 1024 "(x<51)*#"	Numeric/Numeric_122.wav -seed 2
WCreate 1024 "(x<51)*#"	Numeric/Numeric_123.wav -seed 3
WCreate 1024 "(x<51)*#"	Numeric/Numeric_124.wav -seed 4
WCreate 1024 "(x<51)*#"	Numeric/Numeric_125.wav -seed 5
WCreate 1024 "(x<51)*#"	Numeric/Numeric_126.wav -seed 6
WCreate 1024 "(x<51)*#"	Numeric/Numeric_127.wav -seed 7
WCreate 1024 "(x<51)*#"	Numeric/Numeric_128.wav -seed 8
WCreate 1024 "(x<51)*#"	Numeric/Numeric_129.wav -seed 9
WCreate 1024 "(x<57)*#"	Numeric/Numeric_130.wav -seed 0
WCreate 1024 "(x<57)*#"	Numeric/Numeric_131.wav -seed 1
WCreate 1024 "(x<57)*#"	Numeric/Numeric_132.wav -seed 2
WCreate 1024 "(x<57)*#"	Numeric/Numeric_133.wav -seed 3
WCreate 1024 "(x<57)*#"	Numeric/Numeric_134.wav -seed 4
WCreate 1024 "(x<57)*#"	Numeric/Numeric_135.wav -seed 5
WCreate 1024 "(x<57)*#"	Numeric/Numeric_136.wav -seed 6
WCreate 1024 "(x<57)*#"	Numeric/Numeric_137.wav -seed 7
WCreate 1024 "(x<57)*#"	Numeric/Numeric_138.wav -seed 8
WCreate 1024 "(x<57)*#"	Numeric/Numeric_139.wav -seed 9
WCreate 1024 "(x<69)*#"	Numeric/Numeric_140.wav -seed 0
WCreate 1024 "(x<69)*#"	Numeric/Numeric_141.wav -seed 1
WCreate 1024 "(x<69)*#"	Numeric/Numeric_142.wav -seed 2
WCreate 1024 "(x<69)*#"	Numeric/Numeric_143.wav -seed 3
WCreate 1024 "(x<69)*#"	Numeric/Numeric_144.wav -seed 4
WCreate 1024 "(x<69)*#"	Numeric/Numeric_145.wav -seed 5
WCreate 1024 "(x<69)*#"	Numeric/Numeric_146.wav -seed 6
WCreate 1024 "(x<69)*#"	Numeric/Numeric_147.wav -seed 7
WCreate 1024 "(x<69)*#"	Numeric/Numeric_148.wav -seed 8
WCreate 1024 "(x<69)*#"	Numeric/Numeric_149.wav -seed 9
WCreate 1024 "(x<75)*#"	Numeric/Numeric_150.wav -seed 0
WCreate 1024 "(x<75)*#"	Numeric/Numeric_151.wav -seed 1
WCreate 1024 "(x<75)*#"	Numeric/Numeric_152.wav -seed 2
WCreate 1024 "(x<75)*#"	Numeric/Numeric_153.wav -seed 3
WCreate 1024 "(x<75)*#"	Numeric/Numeric_154.wav -seed 4
WCreate 1024 "(x<75)*#"	Numeric/Numeric_155.wav -seed 5
WCreate 1024 "(x<75)*#"	Numeric/Numeric_156.wav -seed 6
WCreate 1024 "(x<75)*#"	Numeric/Numeric_157.wav -seed 7
WCreate 1024 "(x<75)*#"	Numeric/Numeric_158.wav -seed 8
WCreate 1024 "(x<75)*#"	Numeric/Numeric_159.wav -seed 9
WCreate 1024 "(x<81)*#"	Numeric/Numeric_160.wav -seed 0
WCreate 1024 "(x<81)*#"	Numeric/Numeric_161.wav -seed 1
WCreate 1024 "(x<81)*#"	Numeric/Numeric_162.wav -seed 2
WCreate 1024 "(x<81)*#"	Numeric/Numeric_163.wav -seed 3
WCreate 1024 "(x<81)*#"	Numeric/Numeric_164.wav -seed 4
WCreate 1024 "(x<81)*#"	Numeric/Numeric_165.wav -seed 5
WCreate 1024 "(x<81)*#"	Numeric/Numeric_166.wav -seed 6
WCreate 1024 "(x<81)*#"	Numeric/Numeric_167.wav -seed 7
WCreate 1024 "(x<81)*#"	Numeric/Numeric_168.wav -seed 8
WCreate 1024 "(x<81)*#"	Numeric/Numeric_169.wav -seed 9
WCreate 1024 "(x<89)*#"	Numeric/Numeric_170.wav -seed 0
WCreate 1024 "(x<89)*#"	Numeric/Numeric_171.wav -seed 1
WCreate 1024 "(x<89)*#"	Numeric/Numeric_172.wav -seed 2
WCreate 1024 "(x<89)*#"	Numeric/Numeric_173.wav -seed 3
WCreate 1024 "(x<89)*#"	Numeric/Numeric_174.wav -seed 4
WCreate 1024 "(x<89)*#"	Numeric/Numeric_175.wav -seed 5
WCreate 1024 "(x<89)*#"	Numeric/Numeric_176.wav -seed 6
WCreate 1024 "(x<89)*#"	Numeric/Numeric_177.wav -seed 7
WCreate 1024 "(x<89)*#"	Numeric/Numeric_178.wav -seed 8
WCreate 1024 "(x<89)*#"	Numeric/Numeric_179.wav -seed 9
WCreate 1024 "(x<97)*#"	Numeric/Numeric_180.wav -seed 0
WCreate 1024 "(x<97)*#"	Numeric/Numeric_181.wav -seed 1
WCreate 1024 "(x<97)*#"	Numeric/Numeric_182.wav -seed 2
WCreate 1024 "(x<97)*#"	Numeric/Numeric_183.wav -seed 3
WCreate 1024 "(x<97)*#"	Numeric/Numeric_184.wav -seed 4
WCreate 1024 "(x<97)*#"	Numeric/Numeric_185.wav -seed 5
WCreate 1024 "(x<97)*#"	Numeric/Numeric_186.wav -seed 6
WCreate 1024 "(x<97)*#"	Numeric/Numeric_187.wav -seed 7
WCreate 1024 "(x<97)*#"	Numeric/Numeric_188.wav -seed 8
WCreate 1024 "(x<97)*#"	Numeric/Numeric_189.wav -seed 9
WCreate 1024 "(x<103)*#" Numeric/Numeric_190.wav -seed 0
WCreate 1024 "(x<103)*#" Numeric/Numeric_191.wav -seed 1
WCreate 1024 "(x<103)*#" Numeric/Numeric_192.wav -seed 2
WCreate 1024 "(x<103)*#" Numeric/Numeric_193.wav -seed 3
WCreate 1024 "(x<103)*#" Numeric/Numeric_194.wav -seed 4
WCreate 1024 "(x<103)*#" Numeric/Numeric_195.wav -seed 5
WCreate 1024 "(x<103)*#" Numeric/Numeric_196.wav -seed 6
WCreate 1024 "(x<103)*#" Numeric/Numeric_197.wav -seed 7
WCreate 1024 "(x<103)*#" Numeric/Numeric_198.wav -seed 8
WCreate 1024 "(x<103)*#" Numeric/Numeric_199.wav -seed 9
WCreate 1024 "(x<117)*#"	Numeric/Numeric_200.wav -seed 0
WCreate 1024 "(x<117)*#"	Numeric/Numeric_201.wav -seed 1
WCreate 1024 "(x<117)*#"	Numeric/Numeric_202.wav -seed 2
WCreate 1024 "(x<117)*#"	Numeric/Numeric_203.wav -seed 3
WCreate 1024 "(x<117)*#"	Numeric/Numeric_204.wav -seed 4
WCreate 1024 "(x<117)*#"	Numeric/Numeric_205.wav -seed 5
WCreate 1024 "(x<117)*#"	Numeric/Numeric_206.wav -seed 6
WCreate 1024 "(x<117)*#"	Numeric/Numeric_207.wav -seed 7
WCreate 1024 "(x<117)*#"	Numeric/Numeric_208.wav -seed 8
WCreate 1024 "(x<117)*#"	Numeric/Numeric_209.wav -seed 9
WCreate 1024 "(x<131)*#"	Numeric/Numeric_210.wav -seed 0
WCreate 1024 "(x<131)*#"	Numeric/Numeric_211.wav -seed 1
WCreate 1024 "(x<131)*#"	Numeric/Numeric_212.wav -seed 2
WCreate 1024 "(x<131)*#"	Numeric/Numeric_213.wav -seed 3
WCreate 1024 "(x<131)*#"	Numeric/Numeric_214.wav -seed 4
WCreate 1024 "(x<131)*#"	Numeric/Numeric_215.wav -seed 5
WCreate 1024 "(x<131)*#"	Numeric/Numeric_216.wav -seed 6
WCreate 1024 "(x<131)*#"	Numeric/Numeric_217.wav -seed 7
WCreate 1024 "(x<131)*#"	Numeric/Numeric_218.wav -seed 8
WCreate 1024 "(x<131)*#"	Numeric/Numeric_219.wav -seed 9
WCreate 1024 "(x<147)*#"	Numeric/Numeric_220.wav -seed 0
WCreate 1024 "(x<147)*#"	Numeric/Numeric_221.wav -seed 1
WCreate 1024 "(x<147)*#"	Numeric/Numeric_222.wav -seed 2
WCreate 1024 "(x<147)*#"	Numeric/Numeric_223.wav -seed 3
WCreate 1024 "(x<147)*#"	Numeric/Numeric_224.wav -seed 4
WCreate 1024 "(x<147)*#"	Numeric/Numeric_225.wav -seed 5
WCreate 1024 "(x<147)*#"	Numeric/Numeric_226.wav -seed 6
WCreate 1024 "(x<147)*#"	Numeric/Numeric_227.wav -seed 7
WCreate 1024 "(x<147)*#"	Numeric/Numeric_228.wav -seed 8
WCreate 1024 "(x<147)*#"	Numeric/Numeric_229.wav -seed 9
WCreate 1024 "(x<151)*#"	Numeric/Numeric_230.wav -seed 0
WCreate 1024 "(x<151)*#"	Numeric/Numeric_231.wav -seed 1
WCreate 1024 "(x<151)*#"	Numeric/Numeric_232.wav -seed 2
WCreate 1024 "(x<151)*#"	Numeric/Numeric_233.wav -seed 3
WCreate 1024 "(x<151)*#"	Numeric/Numeric_234.wav -seed 4
WCreate 1024 "(x<151)*#"	Numeric/Numeric_235.wav -seed 5
WCreate 1024 "(x<151)*#"	Numeric/Numeric_236.wav -seed 6
WCreate 1024 "(x<151)*#"	Numeric/Numeric_237.wav -seed 7
WCreate 1024 "(x<151)*#"	Numeric/Numeric_238.wav -seed 8
WCreate 1024 "(x<151)*#"	Numeric/Numeric_239.wav -seed 9
WCreate 1024 "(x<163)*#"		Numeric/Numeric_240.wav -seed 0
WCreate 1024 "(x<163)*#"		Numeric/Numeric_241.wav -seed 1
WCreate 1024 "(x<163)*#"		Numeric/Numeric_242.wav -seed 2
WCreate 1024 "(x<163)*#"		Numeric/Numeric_243.wav -seed 3
WCreate 1024 "(x<163)*#"		Numeric/Numeric_244.wav -seed 4
WCreate 1024 "(x<163)*#"		Numeric/Numeric_245.wav -seed 5
WCreate 1024 "(x<163)*#"		Numeric/Numeric_246.wav -seed 6
WCreate 1024 "(x<163)*#"		Numeric/Numeric_247.wav -seed 7
WCreate 1024 "(x<163)*#"		Numeric/Numeric_248.wav -seed 8
WCreate 1024 "(x<163)*#"		Numeric/Numeric_249.wav -seed 9
WCreate 1024 "(x<177)*#"	Numeric/Numeric_250.wav -seed 0
WCreate 1024 "(x<177)*#"	Numeric/Numeric_251.wav -seed 1
WCreate 1024 "(x<177)*#"	Numeric/Numeric_252.wav -seed 2
WCreate 1024 "(x<177)*#"	Numeric/Numeric_253.wav -seed 3
WCreate 1024 "(x<177)*#"	Numeric/Numeric_254.wav -seed 4
WCreate 1024 "(x<177)*#"	Numeric/Numeric_255.wav -seed 5
WCreate 1024 "(x<177)*#"	Numeric/Numeric_256.wav -seed 6
WCreate 1024 "(x<177)*#"	Numeric/Numeric_257.wav -seed 7
WCreate 1024 "(x<177)*#"	Numeric/Numeric_258.wav -seed 8
WCreate 1024 "(x<177)*#"	Numeric/Numeric_259.wav -seed 9
WCreate 1024 "(x<181)*#"	Numeric/Numeric_260.wav -seed 0
WCreate 1024 "(x<181)*#"	Numeric/Numeric_261.wav -seed 1
WCreate 1024 "(x<181)*#"	Numeric/Numeric_262.wav -seed 2
WCreate 1024 "(x<181)*#"	Numeric/Numeric_263.wav -seed 3
WCreate 1024 "(x<181)*#"	Numeric/Numeric_264.wav -seed 4
WCreate 1024 "(x<181)*#"	Numeric/Numeric_265.wav -seed 5
WCreate 1024 "(x<181)*#"	Numeric/Numeric_266.wav -seed 6
WCreate 1024 "(x<181)*#"	Numeric/Numeric_267.wav -seed 7
WCreate 1024 "(x<181)*#"	Numeric/Numeric_268.wav -seed 8
WCreate 1024 "(x<181)*#"	Numeric/Numeric_269.wav -seed 9
WCreate 1024 "(x<199)*#"	Numeric/Numeric_270.wav -seed 0
WCreate 1024 "(x<199)*#"	Numeric/Numeric_271.wav -seed 1
WCreate 1024 "(x<199)*#"	Numeric/Numeric_272.wav -seed 2
WCreate 1024 "(x<199)*#"	Numeric/Numeric_273.wav -seed 3
WCreate 1024 "(x<199)*#"	Numeric/Numeric_274.wav -seed 4
WCreate 1024 "(x<199)*#"	Numeric/Numeric_275.wav -seed 5
WCreate 1024 "(x<199)*#"	Numeric/Numeric_276.wav -seed 6
WCreate 1024 "(x<199)*#"	Numeric/Numeric_277.wav -seed 7
WCreate 1024 "(x<199)*#"	Numeric/Numeric_278.wav -seed 8
WCreate 1024 "(x<199)*#"	Numeric/Numeric_279.wav -seed 9
WCreate 1024 "(x<221)*#"	Numeric/Numeric_280.wav -seed 0
WCreate 1024 "(x<221)*#"	Numeric/Numeric_281.wav -seed 1
WCreate 1024 "(x<221)*#"	Numeric/Numeric_282.wav -seed 2
WCreate 1024 "(x<221)*#"	Numeric/Numeric_283.wav -seed 3
WCreate 1024 "(x<221)*#"	Numeric/Numeric_284.wav -seed 4
WCreate 1024 "(x<221)*#"	Numeric/Numeric_285.wav -seed 5
WCreate 1024 "(x<221)*#"	Numeric/Numeric_286.wav -seed 6
WCreate 1024 "(x<221)*#"	Numeric/Numeric_287.wav -seed 7
WCreate 1024 "(x<221)*#"	Numeric/Numeric_288.wav -seed 8
WCreate 1024 "(x<221)*#"	Numeric/Numeric_289.wav -seed 9
WCreate 1024 "(x<231)*#" 	Numeric/Numeric_290.wav -seed 0
WCreate 1024 "(x<231)*#" 	Numeric/Numeric_291.wav -seed 1
WCreate 1024 "(x<231)*#" 	Numeric/Numeric_292.wav -seed 2
WCreate 1024 "(x<231)*#" 	Numeric/Numeric_293.wav -seed 3
WCreate 1024 "(x<231)*#" 	Numeric/Numeric_294.wav -seed 4
WCreate 1024 "(x<231)*#" 	Numeric/Numeric_295.wav -seed 5
WCreate 1024 "(x<231)*#" 	Numeric/Numeric_296.wav -seed 6
WCreate 1024 "(x<231)*#" 	Numeric/Numeric_297.wav -seed 7
WCreate 1024 "(x<231)*#" 	Numeric/Numeric_298.wav -seed 8
WCreate 1024 "(x<231)*#" 	Numeric/Numeric_299.wav -seed 9
WCreate 1024 "(x<241)*#"	Numeric/Numeric_300.wav -seed 0
WCreate 1024 "(x<241)*#"	Numeric/Numeric_301.wav -seed 1
WCreate 1024 "(x<241)*#"	Numeric/Numeric_302.wav -seed 2
WCreate 1024 "(x<241)*#"	Numeric/Numeric_303.wav -seed 3
WCreate 1024 "(x<241)*#"	Numeric/Numeric_304.wav -seed 4
WCreate 1024 "(x<241)*#"	Numeric/Numeric_305.wav -seed 5
WCreate 1024 "(x<241)*#"	Numeric/Numeric_306.wav -seed 6
WCreate 1024 "(x<241)*#"	Numeric/Numeric_307.wav -seed 7
WCreate 1024 "(x<241)*#"	Numeric/Numeric_308.wav -seed 8
WCreate 1024 "(x<241)*#"	Numeric/Numeric_309.wav -seed 9
WCreate 1024 "(x<251)*#"	Numeric/Numeric_310.wav -seed 0
WCreate 1024 "(x<251)*#"	Numeric/Numeric_311.wav -seed 1
WCreate 1024 "(x<251)*#"	Numeric/Numeric_312.wav -seed 2
WCreate 1024 "(x<251)*#"	Numeric/Numeric_313.wav -seed 3
WCreate 1024 "(x<251)*#"	Numeric/Numeric_314.wav -seed 4
WCreate 1024 "(x<251)*#"	Numeric/Numeric_315.wav -seed 5
WCreate 1024 "(x<251)*#"	Numeric/Numeric_316.wav -seed 6
WCreate 1024 "(x<251)*#"	Numeric/Numeric_317.wav -seed 7
WCreate 1024 "(x<251)*#"	Numeric/Numeric_318.wav -seed 8
WCreate 1024 "(x<251)*#"	Numeric/Numeric_319.wav -seed 9
WCreate 1024 "(x<267)*#"	Numeric/Numeric_320.wav -seed 0
WCreate 1024 "(x<267)*#"	Numeric/Numeric_321.wav -seed 1
WCreate 1024 "(x<267)*#"	Numeric/Numeric_322.wav -seed 2
WCreate 1024 "(x<267)*#"	Numeric/Numeric_323.wav -seed 3
WCreate 1024 "(x<267)*#"	Numeric/Numeric_324.wav -seed 4
WCreate 1024 "(x<267)*#"	Numeric/Numeric_325.wav -seed 5
WCreate 1024 "(x<267)*#"	Numeric/Numeric_326.wav -seed 6
WCreate 1024 "(x<267)*#"	Numeric/Numeric_327.wav -seed 7
WCreate 1024 "(x<267)*#"	Numeric/Numeric_328.wav -seed 8
WCreate 1024 "(x<267)*#"	Numeric/Numeric_329.wav -seed 9
WCreate 1024 "(x<295)*#"	Numeric/Numeric_330.wav -seed 0
WCreate 1024 "(x<295)*#"	Numeric/Numeric_331.wav -seed 1
WCreate 1024 "(x<295)*#"	Numeric/Numeric_332.wav -seed 2
WCreate 1024 "(x<295)*#"	Numeric/Numeric_333.wav -seed 3
WCreate 1024 "(x<295)*#"	Numeric/Numeric_334.wav -seed 4
WCreate 1024 "(x<295)*#"	Numeric/Numeric_335.wav -seed 5
WCreate 1024 "(x<295)*#"	Numeric/Numeric_336.wav -seed 6
WCreate 1024 "(x<295)*#"	Numeric/Numeric_337.wav -seed 7
WCreate 1024 "(x<295)*#"	Numeric/Numeric_338.wav -seed 8
WCreate 1024 "(x<295)*#"	Numeric/Numeric_339.wav -seed 9
WCreate 1024 "(x<311)*#"		Numeric/Numeric_340.wav -seed 0
WCreate 1024 "(x<311)*#"		Numeric/Numeric_341.wav -seed 1
WCreate 1024 "(x<311)*#"		Numeric/Numeric_342.wav -seed 2
WCreate 1024 "(x<311)*#"		Numeric/Numeric_343.wav -seed 3
WCreate 1024 "(x<311)*#"		Numeric/Numeric_344.wav -seed 4
WCreate 1024 "(x<311)*#"		Numeric/Numeric_345.wav -seed 5
WCreate 1024 "(x<311)*#"		Numeric/Numeric_346.wav -seed 6
WCreate 1024 "(x<311)*#"		Numeric/Numeric_347.wav -seed 7
WCreate 1024 "(x<311)*#"		Numeric/Numeric_348.wav -seed 8
WCreate 1024 "(x<311)*#"		Numeric/Numeric_349.wav -seed 9
WCreate 1024 "(x<337)*#"	Numeric/Numeric_350.wav -seed 0
WCreate 1024 "(x<337)*#"	Numeric/Numeric_351.wav -seed 1
WCreate 1024 "(x<337)*#"	Numeric/Numeric_352.wav -seed 2
WCreate 1024 "(x<337)*#"	Numeric/Numeric_353.wav -seed 3
WCreate 1024 "(x<337)*#"	Numeric/Numeric_354.wav -seed 4
WCreate 1024 "(x<337)*#"	Numeric/Numeric_355.wav -seed 5
WCreate 1024 "(x<337)*#"	Numeric/Numeric_356.wav -seed 6
WCreate 1024 "(x<337)*#"	Numeric/Numeric_357.wav -seed 7
WCreate 1024 "(x<337)*#"	Numeric/Numeric_358.wav -seed 8
WCreate 1024 "(x<337)*#"	Numeric/Numeric_359.wav -seed 9
WCreate 1024 "(x<359)*#"	Numeric/Numeric_360.wav -seed 0
WCreate 1024 "(x<359)*#"	Numeric/Numeric_361.wav -seed 1
WCreate 1024 "(x<359)*#"	Numeric/Numeric_362.wav -seed 2
WCreate 1024 "(x<359)*#"	Numeric/Numeric_363.wav -seed 3
WCreate 1024 "(x<359)*#"	Numeric/Numeric_364.wav -seed 4
WCreate 1024 "(x<359)*#"	Numeric/Numeric_365.wav -seed 5
WCreate 1024 "(x<359)*#"	Numeric/Numeric_366.wav -seed 6
WCreate 1024 "(x<359)*#"	Numeric/Numeric_367.wav -seed 7
WCreate 1024 "(x<359)*#"	Numeric/Numeric_368.wav -seed 8
WCreate 1024 "(x<359)*#"	Numeric/Numeric_369.wav -seed 9
WCreate 1024 "(x<371)*#"	Numeric/Numeric_370.wav -seed 0
WCreate 1024 "(x<371)*#"	Numeric/Numeric_371.wav -seed 1
WCreate 1024 "(x<371)*#"	Numeric/Numeric_372.wav -seed 2
WCreate 1024 "(x<371)*#"	Numeric/Numeric_373.wav -seed 3
WCreate 1024 "(x<371)*#"	Numeric/Numeric_374.wav -seed 4
WCreate 1024 "(x<371)*#"	Numeric/Numeric_375.wav -seed 5
WCreate 1024 "(x<371)*#"	Numeric/Numeric_376.wav -seed 6
WCreate 1024 "(x<371)*#"	Numeric/Numeric_377.wav -seed 7
WCreate 1024 "(x<371)*#"	Numeric/Numeric_378.wav -seed 8
WCreate 1024 "(x<371)*#"	Numeric/Numeric_379.wav -seed 9
WCreate 1024 "(x<397)*#"	Numeric/Numeric_380.wav -seed 0
WCreate 1024 "(x<397)*#"	Numeric/Numeric_381.wav -seed 1
WCreate 1024 "(x<397)*#"	Numeric/Numeric_382.wav -seed 2
WCreate 1024 "(x<397)*#"	Numeric/Numeric_383.wav -seed 3
WCreate 1024 "(x<397)*#"	Numeric/Numeric_384.wav -seed 4
WCreate 1024 "(x<397)*#"	Numeric/Numeric_385.wav -seed 5
WCreate 1024 "(x<397)*#"	Numeric/Numeric_386.wav -seed 6
WCreate 1024 "(x<397)*#"	Numeric/Numeric_387.wav -seed 7
WCreate 1024 "(x<397)*#"	Numeric/Numeric_388.wav -seed 8
WCreate 1024 "(x<397)*#"	Numeric/Numeric_389.wav -seed 9
WCreate 1024 "(x<413)*#" 	Numeric/Numeric_390.wav -seed 0
WCreate 1024 "(x<413)*#" 	Numeric/Numeric_391.wav -seed 1
WCreate 1024 "(x<413)*#" 	Numeric/Numeric_392.wav -seed 2
WCreate 1024 "(x<413)*#" 	Numeric/Numeric_393.wav -seed 3
WCreate 1024 "(x<413)*#" 	Numeric/Numeric_394.wav -seed 4
WCreate 1024 "(x<413)*#" 	Numeric/Numeric_395.wav -seed 5
WCreate 1024 "(x<413)*#" 	Numeric/Numeric_396.wav -seed 6
WCreate 1024 "(x<413)*#" 	Numeric/Numeric_397.wav -seed 7
WCreate 1024 "(x<413)*#" 	Numeric/Numeric_398.wav -seed 8
WCreate 1024 "(x<413)*#" 	Numeric/Numeric_399.wav -seed 9


mkdir -p Series
WCreate 1024 "(#>0.7)*(x<18)" Series/Series_000.wav -seed 0
WCreate 1024 "(#>0.7)*(x<18)" Series/Series_001.wav -seed 1
WCreate 1024 "(#>0.7)*(x<18)" Series/Series_002.wav -seed 2
WCreate 1024 "(#>0.7)*(x<18)" Series/Series_003.wav -seed 3
WCreate 1024 "(#>0.7)*(x<18)" Series/Series_004.wav -seed 4
WCreate 1024 "(#>0.7)*(x<18)" Series/Series_005.wav -seed 5
WCreate 1024 "(#>0.7)*(x<18)" Series/Series_006.wav -seed 6
WCreate 1024 "(#>0.7)*(x<18)" Series/Series_007.wav -seed 7
WCreate 1024 "(#>0.7)*(x<18)" Series/Series_008.wav -seed 8
WCreate 1024 "(#>0.7)*(x<18)" Series/Series_009.wav -seed 9
WCreate 1024 "(#>0.7)*(x<25)" Series/Series_010.wav -seed 0
WCreate 1024 "(#>0.7)*(x<25)" Series/Series_011.wav -seed 1
WCreate 1024 "(#>0.7)*(x<25)" Series/Series_012.wav -seed 2
WCreate 1024 "(#>0.7)*(x<25)" Series/Series_013.wav -seed 3
WCreate 1024 "(#>0.7)*(x<25)" Series/Series_014.wav -seed 4
WCreate 1024 "(#>0.7)*(x<25)" Series/Series_015.wav -seed 5
WCreate 1024 "(#>0.7)*(x<25)" Series/Series_016.wav -seed 6
WCreate 1024 "(#>0.7)*(x<25)" Series/Series_017.wav -seed 7
WCreate 1024 "(#>0.7)*(x<25)" Series/Series_018.wav -seed 8
WCreate 1024 "(#>0.7)*(x<25)" Series/Series_019.wav -seed 9
WCreate 1024 "(#>0.8)*(x<35)" Series/Series_020.wav -seed 0
WCreate 1024 "(#>0.8)*(x<35)" Series/Series_021.wav -seed 1
WCreate 1024 "(#>0.8)*(x<35)" Series/Series_022.wav -seed 2
WCreate 1024 "(#>0.8)*(x<35)" Series/Series_023.wav -seed 3
WCreate 1024 "(#>0.8)*(x<35)" Series/Series_024.wav -seed 4
WCreate 1024 "(#>0.8)*(x<35)" Series/Series_025.wav -seed 5
WCreate 1024 "(#>0.8)*(x<35)" Series/Series_026.wav -seed 6
WCreate 1024 "(#>0.8)*(x<35)" Series/Series_027.wav -seed 7
WCreate 1024 "(#>0.8)*(x<35)" Series/Series_028.wav -seed 8
WCreate 1024 "(#>0.8)*(x<35)" Series/Series_029.wav -seed 9
WCreate 1024 "(#>0.8)*(x<51)" Series/Series_030.wav -seed 0
WCreate 1024 "(#>0.8)*(x<51)" Series/Series_031.wav -seed 1
WCreate 1024 "(#>0.8)*(x<51)" Series/Series_032.wav -seed 2
WCreate 1024 "(#>0.8)*(x<51)" Series/Series_033.wav -seed 3
WCreate 1024 "(#>0.8)*(x<51)" Series/Series_034.wav -seed 4
WCreate 1024 "(#>0.8)*(x<51)" Series/Series_035.wav -seed 5
WCreate 1024 "(#>0.8)*(x<51)" Series/Series_036.wav -seed 6
WCreate 1024 "(#>0.8)*(x<51)" Series/Series_037.wav -seed 7
WCreate 1024 "(#>0.8)*(x<51)" Series/Series_038.wav -seed 8
WCreate 1024 "(#>0.8)*(x<51)" Series/Series_039.wav -seed 9
WCreate 1024 "(#>0.8)*(x<61)" Series/Series_040.wav -seed 0
WCreate 1024 "(#>0.8)*(x<61)" Series/Series_041.wav -seed 1
WCreate 1024 "(#>0.8)*(x<61)" Series/Series_042.wav -seed 2
WCreate 1024 "(#>0.8)*(x<61)" Series/Series_043.wav -seed 3
WCreate 1024 "(#>0.8)*(x<61)" Series/Series_044.wav -seed 4
WCreate 1024 "(#>0.8)*(x<61)" Series/Series_045.wav -seed 5
WCreate 1024 "(#>0.8)*(x<61)" Series/Series_046.wav -seed 6
WCreate 1024 "(#>0.8)*(x<61)" Series/Series_047.wav -seed 7
WCreate 1024 "(#>0.8)*(x<61)" Series/Series_048.wav -seed 8
WCreate 1024 "(#>0.8)*(x<61)" Series/Series_049.wav -seed 9
WCreate 1024 "(#>0.85)*(x<79)" Series/Series_050.wav -seed 0
WCreate 1024 "(#>0.85)*(x<79)" Series/Series_051.wav -seed 1
WCreate 1024 "(#>0.85)*(x<79)" Series/Series_052.wav -seed 2
WCreate 1024 "(#>0.85)*(x<79)" Series/Series_053.wav -seed 3
WCreate 1024 "(#>0.85)*(x<79)" Series/Series_054.wav -seed 4
WCreate 1024 "(#>0.85)*(x<79)" Series/Series_055.wav -seed 5
WCreate 1024 "(#>0.85)*(x<79)" Series/Series_056.wav -seed 6
WCreate 1024 "(#>0.85)*(x<79)" Series/Series_057.wav -seed 7
WCreate 1024 "(#>0.85)*(x<79)" Series/Series_058.wav -seed 8
WCreate 1024 "(#>0.85)*(x<79)" Series/Series_059.wav -seed 9
WCreate 1024 "(#>0.85)*(x<97)" Series/Series_060.wav -seed 0
WCreate 1024 "(#>0.85)*(x<97)" Series/Series_061.wav -seed 1
WCreate 1024 "(#>0.85)*(x<97)" Series/Series_062.wav -seed 2
WCreate 1024 "(#>0.85)*(x<97)" Series/Series_063.wav -seed 3
WCreate 1024 "(#>0.85)*(x<97)" Series/Series_064.wav -seed 4
WCreate 1024 "(#>0.85)*(x<97)" Series/Series_065.wav -seed 5
WCreate 1024 "(#>0.85)*(x<97)" Series/Series_066.wav -seed 6
WCreate 1024 "(#>0.85)*(x<97)" Series/Series_067.wav -seed 7
WCreate 1024 "(#>0.85)*(x<97)" Series/Series_068.wav -seed 8
WCreate 1024 "(#>0.85)*(x<97)" Series/Series_069.wav -seed 9



mkdir -p Wavetables
WMorph 64 Sines/sine.wav Triangles/triangle.wav Wavetables/sin_tri.wav
WMorph 64 Sines/sine.wav Squares/square.wav Wavetables/sin_sqr.wav
WMorph 64 Sines/sine.wav Saws/saw.wav Wavetables/sin_saw.wav
WMorph 64 Triangles/triangle.wav Squares/square.wav Wavetables/tri_sqr.wav
WMorph 64 Triangles/triangle.wav Saws/saw.wav Wavetables/tri_saw.wav
WMorph 64 Squares/square.wav Saws/saw.wav Wavetables/sqr_saw.wav

WMorph 64 Sines/sine.wav Buzzes/buzz_00.wav Wavetables/wtable_00.wav
WMorph 64 Sines/sine.wav Buzzes/buzz_10.wav Wavetables/wtable_01.wav
WMorph 64 Sines/sine.wav Buzzes/buzz_20.wav Wavetables/wtable_02.wav
WMorph 64 Sines/sine.wav Buzzes/buzz_30.wav Wavetables/wtable_03.wav
WMorph 64 Sines/sine.wav Buzzes/buzz_40.wav Wavetables/wtable_04.wav

WMorph 64 Squares/square.wav Buzzes/buzz_00.wav Wavetables/wtable_05.wav
WMorph 64 Squares/square.wav Buzzes/buzz_10.wav Wavetables/wtable_06.wav
WMorph 64 Squares/square.wav Buzzes/buzz_20.wav Wavetables/wtable_07.wav
WMorph 64 Squares/square.wav Buzzes/buzz_30.wav Wavetables/wtable_08.wav
WMorph 64 Squares/square.wav Buzzes/buzz_40.wav Wavetables/wtable_09.wav

WMorph 64 Sines/sine_1_2_3_4_5_6_7a.wav Buzzes/buzz_00.wav Wavetables/wtable_10.wav
WMorph 64 Sines/sine_1_2_3_4_5_6_7a.wav Buzzes/buzz_10.wav Wavetables/wtable_11.wav
WMorph 64 Sines/sine_1_2_3_4_5_6_7a.wav Buzzes/buzz_20.wav Wavetables/wtable_12.wav
WMorph 64 Sines/sine_1_2_3_4_5_6_7a.wav Buzzes/buzz_30.wav Wavetables/wtable_13.wav
WMorph 64 Sines/sine_1_2_3_4_5_6_7a.wav Buzzes/buzz_40.wav Wavetables/wtable_14.wav

WMorph 64 Noisy/noisy_00.wav Odd_Partials/odd_3_5_7_9_11_13.wav Wavetables/wtable_15.wav
WMorph 64 Noisy/noisy_03.wav Odd_Partials/odd_3_5_7.wav Wavetables/wtable_16.wav
WMorph 64 Noisy/noisy_05.wav Odd_Partials/odd_3_5.wav Wavetables/wtable_17.wav
WMorph 64 Noisy/noisy_10.wav Odd_Partials/odd_3_5_7_9_11_13.wav Wavetables/wtable_18.wav
WMorph 64 Noisy/noisy_13.wav Odd_Partials/odd_3_5_7.wav Wavetables/wtable_19.wav

WMorph 64 Numeric/Numeric_399.wav Sines/sine.wav Wavetables/wtable_20.wav
WMorph 64 Numeric/Numeric_350.wav Sines/sine.wav Wavetables/wtable_21.wav
WMorph 64 Numeric/Numeric_300.wav Sines/sine.wav Wavetables/wtable_22.wav
WMorph 64 Numeric/Numeric_250.wav Sines/sine.wav Wavetables/wtable_23.wav
WMorph 64 Numeric/Numeric_200.wav Sines/sine.wav Wavetables/wtable_24.wav
WMorph 64 Numeric/Numeric_150.wav Sines/sine.wav Wavetables/wtable_25.wav
WMorph 64 Numeric/Numeric_100.wav Sines/sine.wav Wavetables/wtable_26.wav
WMorph 64 Numeric/Numeric_050.wav Sines/sine.wav Wavetables/wtable_27.wav
WMorph 64 Numeric/Numeric_030.wav Sines/sine.wav Wavetables/wtable_28.wav
WMorph 64 Numeric/Numeric_000.wav Sines/sine.wav Wavetables/wtable_29.wav
WMorph 64 Numeric/Numeric_399.wav Triangles/triangle.wav Wavetables/wtable_30.wav
WMorph 64 Numeric/Numeric_350.wav Triangles/triangle.wav Wavetables/wtable_31.wav
WMorph 64 Numeric/Numeric_300.wav Triangles/triangle.wav Wavetables/wtable_32.wav
WMorph 64 Numeric/Numeric_250.wav Triangles/triangle.wav Wavetables/wtable_33.wav
WMorph 64 Numeric/Numeric_200.wav Triangles/triangle.wav Wavetables/wtable_34.wav
WMorph 64 Numeric/Numeric_150.wav Triangles/triangle.wav Wavetables/wtable_35.wav
WMorph 64 Numeric/Numeric_100.wav Triangles/triangle.wav Wavetables/wtable_36.wav
WMorph 64 Numeric/Numeric_050.wav Triangles/triangle.wav Wavetables/wtable_37.wav
WMorph 64 Numeric/Numeric_030.wav Triangles/triangle.wav Wavetables/wtable_38.wav
WMorph 64 Numeric/Numeric_000.wav Triangles/triangle.wav Wavetables/wtable_39.wav
WMorph 64 Numeric/Numeric_399.wav Squares/square.wav Wavetables/wtable_40.wav
WMorph 64 Numeric/Numeric_350.wav Squares/square.wav Wavetables/wtable_41.wav
WMorph 64 Numeric/Numeric_300.wav Squares/square.wav Wavetables/wtable_42.wav
WMorph 64 Numeric/Numeric_250.wav Squares/square.wav Wavetables/wtable_43.wav
WMorph 64 Numeric/Numeric_200.wav Squares/square.wav Wavetables/wtable_44.wav
WMorph 64 Numeric/Numeric_150.wav Squares/square.wav Wavetables/wtable_45.wav
WMorph 64 Numeric/Numeric_100.wav Squares/square.wav Wavetables/wtable_46.wav
WMorph 64 Numeric/Numeric_050.wav Squares/square.wav Wavetables/wtable_47.wav
WMorph 64 Numeric/Numeric_030.wav Squares/square.wav Wavetables/wtable_48.wav
WMorph 64 Numeric/Numeric_000.wav Squares/square.wav Wavetables/wtable_49.wav
WMorph 64 Numeric/Numeric_399.wav Series/Series_000.wav Wavetables/wtable_50.wav
WMorph 64 Numeric/Numeric_350.wav Series/Series_010.wav Wavetables/wtable_51.wav
WMorph 64 Numeric/Numeric_300.wav Series/Series_015.wav Wavetables/wtable_52.wav
WMorph 64 Numeric/Numeric_250.wav Series/Series_020.wav Wavetables/wtable_53.wav
WMorph 64 Numeric/Numeric_200.wav Series/Series_025.wav Wavetables/wtable_54.wav
WMorph 64 Numeric/Numeric_150.wav Series/Series_030.wav Wavetables/wtable_55.wav
WMorph 64 Numeric/Numeric_100.wav Series/Series_035.wav Wavetables/wtable_56.wav
WMorph 64 Numeric/Numeric_050.wav Series/Series_040.wav Wavetables/wtable_57.wav
WMorph 64 Numeric/Numeric_000.wav Series/Series_045.wav Wavetables/wtable_58.wav
WMorph 64 Numeric/Numeric_000.wav Series/Series_050.wav Wavetables/wtable_59.wav
