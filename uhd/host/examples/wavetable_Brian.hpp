//
// Copyright 2010-2012,2014 Ettus Research LLC
// Copyright 2018 Ettus Research, a National Instruments Company
//
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <cmath>
#include <complex>
#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

// static const size_t wave_table_len = 8192;
static const size_t wave_table_len = 50000;

using namespace std;

class wave_table_class
{
public:
    wave_table_class(const std::string& wave_type, const float ampl)
        : _wave_table(wave_table_len)
    {
        // compute real wave table with 1.0 amplitude
        std::vector<float> real_wave_table(wave_table_len);
        std::vector<float> imag_wave_table(wave_table_len);
        if (wave_type == "OFDM") {

            // file name
            string fileIn = "../build/examples/cosmos_BW_40MHz_Duration_1us.txt";  

            // count row number
            ifstream rowCounter(fileIn);
            int rows = 0;
            string line; // trash
            if(rowCounter.is_open())
            {
                while(!rowCounter.eof())
                {
                    getline(rowCounter,line);
                    rows++;
                    //std::cout<<"hello"<<std::endl;
                }
                rowCounter.close();
            }

            ifstream reader(fileIn);
            rows--; // the last row is blank, so delete it. 

            // assign data type
            double real_wave_table_tmp;
            double imag_wave_table_tmp;

            // read in data
            if (reader.is_open()) {
                for (size_t row_idx = 0; row_idx < rows; row_idx++) {
                    reader >> real_wave_table_tmp;
                    real_wave_table[row_idx] = real_wave_table_tmp;

                    reader >> imag_wave_table_tmp;
                    imag_wave_table[row_idx] = imag_wave_table_tmp;

                    _wave_table[row_idx] = 
                        std::complex<float>(ampl * real_wave_table[row_idx], ampl * imag_wave_table[row_idx]);
                }
            }





        } else if (wave_type == "SINE") {
            static const double tau = 2 * std::acos(-1.0);  // tau = 2pi
            for (size_t i = 0; i < wave_table_len; i++){
                real_wave_table[i] = std::cos((tau * i) / wave_table_len);
                imag_wave_table[i] = std::sin((tau * i) / wave_table_len);
            }

            for (size_t i = 0; i < wave_table_len; i++) {
                _wave_table[i] = std::complex<float>(ampl * real_wave_table[i], 
                ampl * imag_wave_table[i]);
            }
        } else
            throw std::runtime_error("unknown waveform type: " + wave_type);

        




        // // compute i and q pairs with 90% offset and scale to amplitude
        // for (size_t i = 0; i < wave_table_len; i++) {
        //     const size_t q = (i + (3 * wave_table_len) / 4) % wave_table_len;
        //     _wave_table[i] =
        //         std::complex<float>(ampl * real_wave_table[i], ampl * real_wave_table[q]);
        // }

        

    }

    inline std::complex<float> operator()(const size_t index) const
    {
        return _wave_table[index % wave_table_len];
    }

private:
    std::vector<std::complex<float>> _wave_table;
};
