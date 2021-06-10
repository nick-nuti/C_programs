#include <stdio.h>
#include <math.h>
#include "fir.h"

int main () {

	coef_t input_pre[26][7] = {{1,0,0,0.0010,-0.0076,-0.0419,-0.0413},
							   {1,0,0,0.0006,-0.0189,0.1693,0.8295},
							   {1,0,0,0.0007,-0.0049,-0.0324,0.0219},
							   {1,0,0,0,0,0,0},
							   {1,0,0,0,0,0,0},
							   {1,0,0,0,0.0000,0.0000,-0.0000},
							   {1,0,0,0,0,0,0},
							   {1,0,0,0,0,0,0},
							   {1,0,0,0,0.0000,-0.0025,0.0186},
							   {1,0,0,0,-0.0004,-0.0091,0.1157},
							   {1,0,0,-0.0006,-0.0176,0.4083,0.3129},
							   {1,0,0,0,0,0,0},
							   {1,0,0,0,0,0,0},
							   {1,0,0,0,-0.0013,-0.0164,0.4042},
							   {1,0,0,0.0005,-0.0144,0.1278,0.5787},
							   {1,0,0,0,0,0,0},
							   {1,0,0,0,0,0.0002,-0.0003},
							   {1,0,0,0,0.0002,-0.0017,-0.0279},
							   {1,0,0,0,0.0000,0.0004,-0.0014},
							   {1,0,0,0.0001,-0.0022,0.0081,0.1616},
							   {1,0,0,0,0.0000,-0.0000,0.0008},
							   {1,0,0,0.0000,-0.0197,0.2867,0.9391},
							   {1,0,0,0.0000,0.0004,-0.0054,-0.0314},
							   {1,0,0,0,0,0.0000,0.0000},
							   {1,0,0,0,0.0000,0.0001,-0.0002},
							   {1,0,0,0,-0.0055,0.0514,0.5949}};

	coef_t theta_1_pre[7][4] = {{0.2890, -0.1427, 0.1375, -0.0402},
								{0.0077, -0.0016, 0.0247, 0.0127},
								{-0.0003, -0.0055, 0.0009, -0.0009},
								{-0.0843, 0.0455, 0.0487, 0.1000},
								{-0.3052, -0.0680, -0.0472, 0.3983},
								{-0.3977, -0.4722, -0.3125, -0.0184},
								{-0.2209, -0.2556, -0.1011, -0.2383}};

	coef_t theta_2_pre[5][3] = {{-0.8861, -0.3545, 1.3471},
								{-1.8118, 0.6085, 3.5054},
								{-1.5205, 1.07, -2.1386},
								{2.7008, 1.1139, -1.0623},
								{-1.0033, -0.8877, -0.8463}};

	int32_t input[26][7] = {0};
	int32_t layer1[5] = {32768,0,0,0,0}; // **the "one" here is the biasing neuron
	int32_t theta_1[7][4] = {0};
	int32_t theta_2[5][3] = {0};
	int32_t output[3] = {0};

	double actual_out[3] = {0};

	//convert inputs to fixed point 16 bit
	for(int convert1 = 0; convert1 < 26; ++convert1)
		{
			for(int convert2 = 0; convert2 < 7; ++convert2)
			{
				input[convert1][convert2] = (int32_t)((input_pre[convert1][convert2]) * thepower);
			}
		}

	//convert theta1 matrix to fixed point 16 bit
	for(int convert1 = 0; convert1 < 7; ++convert1)
	{
		for(int convert2 = 0; convert2 < 4; ++convert2)
		{
			theta_1[convert1][convert2] = (int32_t)((theta_1_pre[convert1][convert2]) * thepower);
		}
	}

	//convert theta2 matrix to fixed point 16 bit
	for(int convert1 = 0; convert1 < 5; ++convert1)
	{
		for(int convert2 = 0; convert2 < 3; ++convert2)
		{
			theta_2[convert1][convert2] = (int32_t)((theta_2_pre[convert1][convert2] / 4) * thepower);
		}
	}

	post_matrix theta1_s = {.rows = 7,
						    .columns = 4,
						    .matrix_values = &theta_1[0][0]
						   };

	post_matrix theta2_s = {.rows = 5,
						    .columns = 3,
						    .matrix_values = &theta_2[0][0]
						   };

	post_matrix layer1_s = {.rows = 1,
						    .columns = 5,
						    .matrix_values = layer1
						   };

	post_matrix output_s = {.rows = 1,
							.columns = 3,
							.matrix_values = output
						   };

	for(int input_row = 0; input_row < 26; ++input_row)
	{
		post_matrix input_s = {.rows = 1,
							   .columns = 8,
							   .matrix_values = input[input_row]
							  };

		fir(&input_s, &theta1_s, &layer1_s, true);

		//for(int a = 0; a < layer1_s.columns; ++a)
		//{
		//	printf("%d ", layer1_s.matrix_values[a]);
		//}

		//printf("\n");

		fir(&layer1_s, &theta2_s, &output_s, false);

		//convert each value then print out
		for(int outtie = 0; outtie < output_s.columns; ++outtie)
		{
			actual_out[outtie] = (double) (output_s.matrix_values[outtie]) / thepower;
			printf("%f ", actual_out[outtie]);
		}

		printf("\n");

	}
	return 0;
}
