#include <stdio.h>
#include <math.h>
#include "fir.h"

// ex: post_matrix *fir_input -> &input_s in fir(&input_s, &theta1_s, &layer1_s);
// we're doing this * and & so we aren't copying the instance of the struct... we're using the struct we've already created
// the "fir_input->columns" below is the same as (*fir_input).columns and the pointer is required because we still need to grab the original data with the pointer

// int a;
// &a -> address of that variable
// int *a_ptr;
// &a_ptr -> address of the pointer
// a_ptr // address we're pointing to
// *a_ptr // value at the address we're point int to

void fir(post_matrix *fir_input, post_matrix *fir_theta, post_matrix *fir_output, bool bias_neuron)
{
	int32_t intermittent_matrix[fir_output->columns];
	int32_t *theta_address = fir_theta->matrix_values;

	// w x j * j x n  = w x n matrix
	for(int n = 0; n < fir_theta->columns; ++n)
	{
		intermittent_matrix[n] = 0;

		for(int j = 0; j < fir_theta->rows; ++j)
		{
			intermittent_matrix[n] += ( fir_input->matrix_values[j] * *(theta_address + (j * (fir_theta->columns) + n)) );
			//printf("inputs = %d\n", fir_input->matrix_values[j]);
			//printf("thetas = %d\n", *(theta_address + (j * (fir_theta->columns) + n)));
		}

		intermittent_matrix[n] = intermittent_matrix[n] / thepower; // after multiplication, need to divide by 16-bit power because 2 16-bit fixed-point values were multiplied together
		//printf("intermittent_matrix[n] = %d\n", intermittent_matrix[n]);
	}

	//printf("\n");

	for(int relu = 0; relu < fir_theta->columns; ++relu)
	{
		// index for fir_output is shifted so we don't disturb 1 biasing neuron
		int relu_out;

		if(bias_neuron == true) relu_out = relu+1;
		else relu_out = relu;

		if(intermittent_matrix[relu] >= 0) fir_output->matrix_values[relu_out] = intermittent_matrix[relu];
		else fir_output->matrix_values[relu_out] = 0;

		//printf("intermittent_matrix = %d\n", intermittent_matrix[relu]);
		//printf("matrix_values = %d\n", fir_output->matrix_values[relu_out]);
	}

	//printf("\n");

	/*
	static data_t shift_reg[n];
	acc_t acc;
	data_t data;
	int i;

	acc=0;

	for (i=n-1;i>=0;i--)
	{
	  if (i==0)
	  {
		shift_reg[0]=x;
		data = x;
	  }

	  else
	  {
		shift_reg[i]=shift_reg[i-1];
		data = shift_reg[i];
	   }

	  acc+=data*c[i];
	}

	*y=acc;
	*/
}
