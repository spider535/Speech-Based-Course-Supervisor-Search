#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma once
#define N 5
#define M 32
#define T 40

namespace project {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>

	double max = -99999999 , min = 9999999999;    // helping variable use to find maximum
	double sample[320];     //this is use to collect sample data from text file
	double R[14];           // this is use to store Ri's calculated
	double A_i[13];           // this is use to store Ai's calculated
	double C[14];           // this is use to store Ci's calculated
	double a[14][14] , K[14] , E[14];    //helping variables
	double sigma;        //this is use to calculate C[0]
	double sum = 0;                 //helping variable
	double W[12] = {1.0, 3.0, 7.0, 13.0, 19.0, 22.0, 25.0, 33.0, 42.0, 50.0, 56.0, 61.0 };
	int i = 0 , j = 0 , k = 0 , t = 0  , m = 0 ,digit = 0 , temp1 , iterator = 0 , temp_index = -1 , obs_seq = -1 , temp_digit = -1 , choice = 1 , count = 0;
	
	long double A[20][N][N] , B[20][N][M] , temp , Pi[20][N] ; 
	long double alpha[T+1][N]  ,temp_max = -9999999, result = 0 ,prev_result = -1, beta[T+1][N] , delta[T+1][N] , psi[T+1][N] , p_star , Xi[T+1][N][N] , gama[T+1][N] , temp2 = 0 , temp3 = 0;
	int qt_star[T+1] ;
	int O[T+1];
	char utterance[40];
	char * buffer = new char[1024];
	char c[1000];
	char * line , *ptr;  
	FILE *myFile , *myFile_1;

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:


		Form1(void)
		{
			InitializeComponent();
			//
			
			
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  Train;

	private: System::Windows::Forms::Button^  Test;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;

	protected: 

	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->Train = (gcnew System::Windows::Forms::Button());
			this->Test = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// Train
			// 
			this->Train->BackColor = System::Drawing::SystemColors::MenuHighlight;
			this->Train->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 26.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Train->ForeColor = System::Drawing::SystemColors::ControlText;
			this->Train->Location = System::Drawing::Point(86, 291);
			this->Train->Name = L"Train";
			this->Train->Size = System::Drawing::Size(162, 77);
			this->Train->TabIndex = 0;
			this->Train->Text = L"Train";
			this->Train->UseVisualStyleBackColor = false;
			this->Train->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// Test
			// 
			this->Test->BackColor = System::Drawing::SystemColors::MenuHighlight;
			this->Test->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 26.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Test->Location = System::Drawing::Point(337, 291);
			this->Test->Name = L"Test";
			this->Test->Size = System::Drawing::Size(163, 77);
			this->Test->TabIndex = 1;
			this->Test->Text = L"Test";
			this->Test->UseVisualStyleBackColor = false;
			this->Test->Click += gcnew System::EventHandler(this, &Form1::button1_Click_1);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(119, 65);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(349, 195);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 2;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(12, 12);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(90, 88);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox2->TabIndex = 3;
			this->pictureBox2->TabStop = false;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(593, 409);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->Test);
			this->Controls->Add(this->Train);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

// training data-----------------------------------------------------------------------
		for(digit = 0 ; digit < 10 ; digit++)
		{
			MessageBox::Show("Train Digit - " + digit);
			printf("\n\n-------------------------- Digit - %d ----------------------\n",digit); 
			for(i = 0 ; i < 20 ; i++)
			{
				Pi[i][0] = 1;
				for(k = 1 ; k < N ; k++)
				{
					Pi[i][k] = 0;
				}
			}


			for(i = 0 ; i < 20 ; i++)
			{
				for(j = 0 ; j < N ; j++)
				{
					for(k = 0 ; k < M ; k++)
					{
						B[i][j][k] = 0.03125;
					}
				}
			}

			for(i = 0 ; i < 20 ; i++)
			{
				for(j = 0 ; j < N ; j++)
				{
					for(k = 0 ; k < N ; k++)
					{
						A[i][j][k] = 0;
					}
				}
			}

			for(i = 0 ; i < 20 ; i++)
			{
				for(j = 0 ; j < N ; j++)
				{
					if(j == N-1)
					{
						A[i][j][j] = 1;
					}
					else
					{
						A[i][j][j] = 0.8;
						A[i][j][j+1] = 0.2;
					}
				}
			}


			//---------------------------------------------------------------------

		
			for(int ut = 0 ; ut < 20 ; ut++)               // iteration for  20 utterance of each digit
			{
				for(i = 0; i <= T ; i++)
				{
					O[i] = -1;
				}
			
				sprintf(utterance, "Training/Digit_%d/%d_%d.txt",digit , digit , ut+1);
				myFile = fopen(utterance, "r");              // reading training file
				if (myFile == NULL)
				{
					printf("Error Reading File\n");
					exit (0);
				}
				for(i = 0 ; i < 320 ; i++)
				{
					sample[i] = 0;
				}
				while(abs(sample[0]) < 150)                   // remove silence
					fscanf(myFile ,"%lf", &sample[0]);
				if(feof(myFile))
				{
					printf("Error Reading File\n");
					exit (0);
				}
		
				//--------------------------------------------------
				//printf("\n\n\n");
				for(j = 240;j<320;j++)
				{
					fscanf(myFile, "%lf", &sample[j]);
				}
				for(t = 1 ; t <= T ; t++)
				{
			
					for(j = 0 ; j < 80 ; j++)
					{
						sample[j] = sample[240+j];
						if(abs(sample[j]) > max)             
						{
							max = abs(sample[j]);
						}
					}

					for( j = 80 ; j < 320 ; j++)
					{
						fscanf(myFile, "%lf", &sample[j]);    // reading data of 320 sample for frame

						// calculating max use to find normalization
						if(abs(sample[j]) > max)             
						{
							max = abs(sample[j]);
						}
					}

					//normalize

					for( j = 0 ; j < 320 ; j++)
					{
						sample[j] = (sample[j] * 5000) / max;
					}
					max = -99999999;

			
					//calculating R[i]
			
					for(i = 0 ; i < 13 ; i++)
					{
						R[i] = 0;
						for(j = 0 ; j < 320 - i ; j++)
						{
							R[i] += sample[j] * sample[i + j];
						}
					}

					
					//calculating A[i]

					E[0] = R[0];

					for( i = 1 ; i < 13 ; i++)
					{
						sum = 0;
						for(int j = 1 ; j < i ; j++)
						{
							sum += a[i - 1][j] * R[i - j];
						}	
	
						K[i] = ( R[i] - sum ) / E[i - 1];
						a[i][i] = K[i];
						for(int j = 0 ; j < i ; j++)
						{
							a[i][j] = a[i - 1][j] - K[i] * a[i - 1][i - j];
						}
						E[i] = ( 1 - K[i] * K[i] ) * E[i - 1];
					}
	
					for(i = 1 ; i < 13 ; i++)
					{
						A_i[i] = a[12][i] ;
					}

					//calculating C[i]

					sigma = R[0];
					C[0] = log(sigma * sigma);

					for( m = 1 ; m < 13 ; m++)
					{
						sum = 0;
						for( k = 1 ; k < m ; k++)
						{
							sum += (k * C[k] * A_i[m - k]) / m;
						}
						C[m] = A_i[m] + sum;
					}


					//apply raised sine window on Ci
					for(int i = 1 ; i < 13 ; i++)
					{
						C[i] *= (1 + (6 * sin((3.14 * i) / 12)));
					}


					double Cr;
					min = 99999999999;
					obs_seq = -1;
					myFile_1 = fopen("codebook.txt", "r");
					for(j = 1 ; j <= 32 ; j++)
					{
						sum = 0;
						for(int i = 1 ; i < 13 ; i++)
						{
							fscanf(myFile_1 ,"%lf", &Cr);
							sum += ( W[i - 1] * (C[i] - Cr) *  (C[i] - Cr) );     // calculating Thokura distance
						}
						if(min > sum )
						{
							min = sum;
							obs_seq = j;
						}
					}
					fclose(myFile_1);
					O[t] = obs_seq;
				}

				fclose(myFile);         // closing file
		
		
		
				printf("\n\nObservation Sequence %d ---------------------\n\n", ut+1);
				for(t = 1 ; t <= T ; t++)
				{
					printf("%d " , O[t]);
				}
				printf("\n\n");
				iterator = 0 ;
				while(iterator != 200)
				{
					//prev_result = result;
					iterator++;
					//printf("\n\n-------------%d Iterator-------------------\n",iterator);
					//solution to problem 1
					//forward procedure
					//printf("\n\n-------------Forward procedure-------------------\n");
					//initialization
					for(i = 0 ; i < N ; i++)
					{
						alpha[1][i] = Pi[ut][i]*B[ut][i][O[1]-1];
					}

					//induction
					for(t = 1 ; t < T ; t++)
					{
						for(j =0 ; j < N ; j++)
						{
							temp = 0;
							for(i = 0 ; i < N ; i++)
							{
								temp += alpha[t][i] * A[ut][i][j] ;
							}
							temp *= B[ut][j][O[t+1]-1];
							alpha[t+1][j] = temp;
						}
					}

					//termination
					result = 0;
					for(i = 0 ; i < N ; i++)
					{
						result += alpha[T][i];
					}

					//printf("\nProbability P for given lembda is %g \n",result);
	
	
					//Backward procedure
					//printf("\n-------------Backward procedure-------------------\n");
					//initialize
					for(i = 0 ; i < N ; i++)
					{
						beta[T][i] = 1 ;
					}

					//induction
					for(t = T-1 ; t > 0 ; t--)
					{
						for(i = 0 ; i < N ; i++)
						{
							temp = 0;
							for(j = 0 ; j < N ; j++)
							{
								temp += A[ut][i][j] * B[ut][j][O[t+1]-1] * beta[t+1][j];
							}
							beta[t][i] = temp;
						}
					}

					

					//solution to problem 2 
					//viterbi algorithm
					//printf("\n\n------------Viterbi Algorithm---------------\n");

					//initialize

					for(i = 0 ; i < N ; i++)
					{
						delta[1][i] = Pi[ut][i] * B[ut][i][O[1]-1] ;
						psi[1][i] = 0 ;
					}

					//recursion
					for(t = 2 ; t <=T ;t++)
					{
						for(j = 0 ; j < N ; j++ )
						{
							delta[t][j] = 0;
							psi[t][j] = -1;
							for(i = 0 ; i < N ; i++)
							{
								temp = delta[t-1][i] * A[ut][i][j] ;
								if( temp > delta[t][j] )
								{
									delta[t][j] = temp;
									psi[t][j] = i;
								}
							}
							delta[t][j] *= B[ut][j][O[t]-1] ;
						}
					}


					//termination 
					p_star = 0;
					qt_star[T] = -1;
					for(i = 0 ; i < N ; i++)
					{
						if( delta[T][i] > p_star )
						{
							p_star = delta[T][i];
							qt_star[T] = i ;
						}
					}

					//backtracking
					for(t = T - 1 ; t > 0 ; t--)
					{
						qt_star[t] = psi[t+1][qt_star[t+1]] ;
					}

					
					//Xi and gama initialization
					for(t = 1 ; t <= T ; t++)
					{
						for(i = 0 ; i < N ; i++)
						{
							gama[t][i] = 0;
							for(j = 0 ; j < N ; j++)
							{
								Xi[t][i][j] = 0 ;
							}
						}
					}


					for(t = 1 ; t < T ; t++)
					{
						for(i = 0 ; i < N ; i++)
						{
							for(j = 0 ; j < N ; j++)
							{
								Xi[t][i][j] = (alpha[t][i] * A[ut][i][j] * B[ut][j][O[t+1]-1] * beta [t+1][j] ) / result ;
							}
						}
					}

					for(t = 1 ; t < T ; t++)
					{
						for(i = 0 ; i < N ; i++)
						{
							gama[t][i] = 0;
							for(j = 0 ; j < N ; j++)
							{
								gama[t][i] += Xi[t][i][j];
							}
						}
					}


					//reestimation --------

					for( i = 0 ; i < N ; i++)
					{
						Pi[0][i] = gama[1][i] ;
					}

					for( i = 0 ; i < N ; i++)
					{
						for( j = 0 ; j < N ; j++)
						{
							temp2 = 0 ;
							temp3 = 0 ;
							for(t = 1 ; t < T ; t++)
							{
								temp2 += Xi[t][i][j] ;
								temp3 += gama[t][i] ;
							}
							A[ut][i][j] = temp2 / temp3 ;
						}
						temp2 = 0;
						temp3 = 0;
						temp_index = -1;
						for( j = 0 ; j < N ; j++)
						{
							temp2 += A[ut][i][j];
							if(temp3 < A[ut][i][j])
							{
								temp3 = A[ut][i][j];
								temp_index = j;
							}
						}
						temp2 = 1 - temp2 ;
						A[ut][i][temp_index] += temp2; 

					}

					for( i = 0 ; i < N ; i++)
					{
						for( j = 0 ; j < M ; j++)
						{
							temp2 = 0 ;
							temp3 = 0 ;
							for(t = 1 ; t <= T ; t++)
							{
								if( (O[t]-1) ==  j)
								{
									temp2 += gama[t][i] ;
								}

								temp3 += gama[t][i] ;
							}

							B[ut][i][j] = temp2 / temp3 ;
							if(B[ut][i][j] == 0)
							{
								B[ut][i][j] = 1e-030 ;
							}
						}
						temp2 = 0;
						temp3 = 0;
						temp_index = -1;
						for( j = 0 ; j < M ; j++)
						{
							temp2 += B[ut][i][j];
							if(temp3 < B[ut][i][j])
							{
								temp3 = B[ut][i][j];
								temp_index = j;
							}
						}
						temp2 = 1 - temp2 ;
						B[ut][i][temp_index] += temp2; 
					}
		
				}

				for(t = 1 ; t <= T ; t++)
				{
					printf("%d ",qt_star[t] + 1);
				}
			
				printf("\n\nProbability = %g  -------------------\n",p_star);
				//printf("\nTotal Iterator = %d  -------------------\n",iterator);
				printf("\n\n----final Pi Matrix ---------\n");

				for( i = 0 ; i < N ; i++)
				{
					printf("%g  ",Pi[ut][i]);
				}

				printf("\n\n-------final A Matrix- ------------\n");

				for( i = 0 ; i < N ; i++)
				{
					printf("\n");
					for( j = 0 ; j < N ; j++)
					{
						printf("%g  ",A[ut][i][j]);
					}
				}

				printf("\n\n-------final B Matrix- ------------\n");
	
				for( i = 0 ; i < N ; i++)
				{
					printf("\n");
					for( j = 0 ; j < M ; j++)
					{
						printf("%g  ",B[ut][i][j]);
					}
				}
			
	
				printf("\n\n");

			}


			
			//avarage model------------------------
			//printf("Final Converged Lembda--------------");
			//Pi---------------------
			for( i = 0 ; i < N ; i++)
			{
				temp = 0;
				for(k = 0 ; k < 20 ; k++)
				{
					temp += Pi[k][i];
				}
				Pi[0][i] = temp / 20 ;
			}

			// A matrix------------------

			for( i = 0 ; i < N ; i++)
			{
				for( j = 0 ; j < N ; j++)
				{
					temp = 0;
					for(k = 0 ; k < 20 ; k++)
					{
						temp += A[k][i][j];
					}
					A[0][i][j] = temp / 20 ;
				}
				temp2 = 0;
				temp3 = 0;
				temp_index = -1;
				for( j = 0 ; j < N ; j++)
				{
					temp2 += A[0][i][j];
					if(temp3 < A[0][i][j])
					{
						temp3 = A[0][i][j];
						temp_index = j;
					}
				}
				temp2 = 1 - temp2 ;
				A[0][i][temp_index] += temp2; 
			}

			// B matrix--------------------

			for( i = 0 ; i < N ; i++)
			{
				for( j = 0 ; j < M ; j++)
				{
					temp = 0;
					for(k = 0 ; k < 20 ; k++)
					{
						temp += B[k][i][j];
					}
					B[0][i][j] = temp / 20 ;
				}
				temp2 = 0;
				temp3 = 0;
				temp_index = -1;
				for( j = 0 ; j < M ; j++)
				{
					temp2 += B[0][i][j];
					if(temp3 < B[0][i][j])
					{
						temp3 = B[0][i][j];
						temp_index = j;
					}
				}
				temp2 = 1 - temp2 ;
				B[0][i][temp_index] += temp2; 
			}

			sprintf(utterance, "Testing/Digit_%d/Pi_matrix.txt",digit);
			myFile = fopen(utterance,"w");

			//printf("\n\n----Converged Pi Matrix ---------\n");

			for( i = 0 ; i < N ; i++)
			{
				fprintf(myFile , "%g\t" ,Pi[0][i]);
				//printf("%g  ",Pi[0][i]);
			}

			fclose(myFile);

			sprintf(utterance, "Testing/Digit_%d/A_matrix.txt",digit);
			myFile = fopen(utterance,"w");
			//printf("\n\n-------Converged A Matrix- ------------\n");

			for( i = 0 ; i < N ; i++)
			{
				printf("\n");
				for( j = 0 ; j < N ; j++)
				{
					fprintf(myFile , "%g\t" ,A[0][i][j]);
					//printf("%g  ",A[0][i][j]);
				}
				fprintf(myFile , "\n");
			}

			fclose(myFile);

			sprintf(utterance, "Testing/Digit_%d/B_matrix.txt",digit);
			myFile = fopen(utterance,"w");
			//printf("\n\n-------Converged B Matrix- ------------\n");
	
			for( i = 0 ; i < N ; i++)
			{
				printf("\n");
				for( j = 0 ; j < M ; j++)
				{
					fprintf(myFile , "%g\t" ,B[0][i][j]);
					//printf("%g  ",B[0][i][j]);
				}
				fprintf(myFile , "\n");
			}

			fclose(myFile);
	
			printf("\n\n");

		}

		MessageBox::Show("Trained Successfully!!!!!!");

			 }
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e) {


// Testing----------------------------------------------------------
	MessageBox::Show("\n Welcome to test Speech based Supervisor Search\n");
	
	choice = -1;
	while(choice != 9)
	{
		choice = -1;

		MessageBox::Show("\n Choose which subject supervisor you want\n--------------------------------------------------------\n 1. Algorithm \n 2. Database Mangement System\n 3. Operating System \n 4. Speech Processing\n 5. Network\n 6. Machine Learning\n 7. Discrete Maths\n 8. Software Engineering\n 9. Exit\n");

		system("Recording_Module.exe 3 live_in.wav live_out.txt");
		sprintf(utterance, "live_out.txt" );
		myFile = fopen(utterance, "r");              
		if (myFile == NULL)
		{
			printf("Error Reading File\n");
			exit (0);
		}
		for(i = 0 ; i < 320 ; i++)
		{
			sample[i] = 0;
		}
		while(abs(sample[0]) < 150)                   // remove silence
			fscanf(myFile ,"%lf", &sample[0]);
		if(feof(myFile))
		{
			printf("Error Reading File\n");
			exit (0);
		}
		
		//--------------------------------------------------
		//printf("\n\n\n");
		for(j = 240;j<320;j++)
		{
			fscanf(myFile, "%lf", &sample[j]);
		}
		for(t = 1 ; t <= T ; t++)
		{
			
			for(j = 0 ; j < 80 ; j++)
			{
				sample[j] = sample[240+j];
				if(abs(sample[j]) > max)             
				{
					max = abs(sample[j]);
				}
			}

			for( j = 80 ; j < 320 ; j++)
			{
				fscanf(myFile, "%lf", &sample[j]);    // reading data of 320 sample for frame

				// calculating max use to find normalization
				if(abs(sample[j]) > max)             
				{
					max = abs(sample[j]);
				}
			}

			//normalize

			for( j = 0 ; j < 320 ; j++)
			{
				sample[j] = (sample[j] * 5000) / max;
			}
			max = -99999999;

			
			//calculating R[i]
			
			for(i = 0 ; i < 13 ; i++)
			{
				R[i] = 0;
				for(j = 0 ; j < 320 - i ; j++)
				{
					R[i] += sample[j] * sample[i + j];
				}
			}

			
	
			//calculating A[i]

			E[0] = R[0];

			for( i = 1 ; i < 13 ; i++)
			{
				sum = 0;
				for(int j = 1 ; j < i ; j++)
				{
					sum += a[i - 1][j] * R[i - j];
				}	
	
				K[i] = ( R[i] - sum ) / E[i - 1];
				a[i][i] = K[i];
				for(int j = 0 ; j < i ; j++)
				{
					a[i][j] = a[i - 1][j] - K[i] * a[i - 1][i - j];
				}
				E[i] = ( 1 - K[i] * K[i] ) * E[i - 1];
			}
	
			for(i = 1 ; i < 13 ; i++)
			{
				A_i[i] = a[12][i] ;
			}

			
			//calculating C[i]

			sigma = R[0];
			C[0] = log(sigma * sigma);

			for( m = 1 ; m < 13 ; m++)
			{
				sum = 0;
				for( k = 1 ; k < m ; k++)
				{
					sum += (k * C[k] * A_i[m - k]) / m;
				}
				C[m] = A_i[m] + sum;
			}


			//apply raised sine window on Ci
			for(int i = 1 ; i < 13 ; i++)
			{
				C[i] *= (1 + (6 * sin((3.14 * i) / 12)));
			}


			double Cr;
			min = 99999999999;
			obs_seq = -1;
			myFile_1 = fopen("codebook.txt", "r");
			for(j = 1 ; j <= 32 ; j++)
			{
				sum = 0;
				for(int i = 1 ; i < 13 ; i++)
				{
					fscanf(myFile_1 ,"%lf", &Cr);
					sum += ( W[i - 1] * (C[i] - Cr) *  (C[i] - Cr) );     // calculating Thokura distance
				}
				if(min > sum )
				{
					min = sum;
					obs_seq = j;
				}
			}
			fclose(myFile_1);
			O[t] = obs_seq;
		}

		fclose(myFile);         // closing file
		
		
		
		temp_max = -99999999;
		temp_digit = -1;
		for(k = 0 ; k < 10 ; k++)
		{
			sprintf(utterance, "Testing/Digit_%d/Pi_matrix.txt",k );
			myFile = fopen(utterance, "r");
			if (myFile == NULL)
			{
				printf("Error Reading File\n");
				exit (0);
			}
			fgets(buffer,1024,myFile);
			line = strtok(buffer,"\t"); 
		
			j = 0;
			while (line != NULL) 
			{
				if(j<N)
				{
					Pi[0][j] = strtod(line,&ptr);
				}
				++j;
				line = strtok(NULL,"\t");
			}

			fclose(myFile);

				
			sprintf(utterance, "Testing/Digit_%d/A_matrix.txt",k );
			myFile = fopen(utterance, "r");
			if (myFile == NULL)
			{
				printf("Error Reading File\n");
				exit (0);
			}
			i=0;
			while(fgets(buffer,1024,myFile))
			{
				line = strtok(buffer,"\t"); 
		
				j = 0;
				while (line != NULL) 
				{
					if(j<N)
					{
						A[0][i][j] = strtod(line,&ptr);
					}
					++j;
					line = strtok(NULL,"\t");
				}
				++i;
			}

			fclose(myFile);

			sprintf(utterance, "Testing/Digit_%d/B_matrix.txt",k);
			myFile = fopen(utterance, "r");
			if (myFile == NULL)
			{
				printf("Error Reading File\n");
				exit (0);
			}
			i=0;
			while(fgets(buffer,1024,myFile))
			{
				line = strtok(buffer,"\t"); 
				j = 0;
				while (line != NULL) 
				{
					if(i < N && j < M)
					{
						B[0][i][j] = strtod(line,&ptr);
					}
					++j;
					line = strtok(NULL,"\t");
				}
				++i;
			}
			fclose(myFile);

				
			//solution to problem 1
			//forward procedure
			//printf("\n\n-------------Forward procedure-------------------\n");
			//initialization
			for(i = 0 ; i < N ; i++)
			{
				alpha[1][i] = Pi[0][i]*B[0][i][O[1]-1];
			}

			//induction
			for(t = 1 ; t < T ; t++)
			{
				for(j =0 ; j < N ; j++)
				{
					temp = 0;
					for(i = 0 ; i < N ; i++)
					{
						temp += alpha[t][i] * A[0][i][j] ;
					}
					temp *= B[0][j][O[t+1]-1];
					alpha[t+1][j] = temp;
				}
			}

			//termination
			result = 0;
			for(i = 0 ; i < N ; i++)
			{
				result += alpha[T][i];
			}

			//printf("\nP value for Digit %d is %g \n" , k , result);

			if(temp_max < result)
			{
				temp_max = result;
				temp_digit = k;
			}

		}

		//printf("\nDigit is recognized as  %d ----------\n",temp_digit);
		choice = temp_digit;

		switch(choice)
		{

		case 1:
			MessageBox::Show("\n1. Algorithm Professor List ---------\n\nProf. Pradip Kr. Das\nProf. Sukanta Bhattacharjee ");

			break;

		case 2:
			MessageBox::Show("\n2. Database Management System Professor List ---------\n\nProf. Rashmi Dutta Baruah \nProf. Diganta Goswami");
			
			break;

		case 3:
			MessageBox::Show("\n3. Operating System Professor List ---------\n\nDr. John Jose\nDr.Tamarapalli Venkatesh");

			break;

		case 4:
			MessageBox::Show("\n4. Speech Processing Professor List ---------\n\nProf Pradip Kr. Das");

			break;

		case 5:
			MessageBox::Show("\n5. Network Professor List ---------\n\nDr. Manas Khatua\nProf. S. V. Rao");

			break;

		case 6:
			MessageBox::Show("\n6. Machine Learning Professor List ---------\n\nDr. Ashish anand\nDr. Arijit Sur");

			break;

		case 7:
			MessageBox::Show("\n7. Discrete Maths Professor List ---------\n\nProf. G. Sajith\nDr. Rajasekhar Inkulu");

			break;

		case 8:
			MessageBox::Show("\n8. Software Engineering Professor List ---------\n\nDr. V. Vijaya Saradhi\nProf. Diganta Goswami");

			break;

		case 9:
			MessageBox::Show("Thanks For Visiting !!!!!!!");
		
			break;

		default:

			MessageBox::Show("\nSorry ! Word is not Recognized Please Try Again -------\n");


		}


	}

			 }
	};
}

