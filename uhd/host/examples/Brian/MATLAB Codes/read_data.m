clc;clear;
close all



% % directory = 'D:\Storage\OneDrive - University of Southern California\Documents\USC\WiDes\Projects\1st Year\COSMOS\SB1 Files\host\demos\basic\Result';
% directory = 'C:\Storage\OneDrive - University of Southern California\Documents\USC\WiDes\Projects\1st Year\COSMOS\SB1 Files\host\demos\basic\Result\';
% 
% group_ID = 2;
% subgroup_ID = 2;
% measurement_ID = 1;
% directory = [directory, 'Group_', num2str(group_ID)];
% % ====== Measurement Profile ======
% 
% 
% 
% 
% 
% 
% 
% 
% 
% % =================================




%% Tx signal SINE
wfm_freq = 1e6;
tx_sampling_rate = 10e6;
signal_len = 8192;
buff_size = 15000;



signal_tmp = zeros(signal_len, 1);
for i = 1:signal_len
    signal_tmp(i) = sin((2*pi*(i-1))/signal_len);   
end
% figure;
% plot(1:signal_len,signal_tmp)

% signal is just a single sine wave, no frequency has been set
signal = zeros(signal_len, 1);
for i = 1:signal_len
    q = mod((i + (3 * signal_len) / 4),  signal_len);
    signal(i) = signal_tmp(i) + 1j * signal_tmp(q+1);
end
% figure;plot(1:signal_len, 20*log10(abs(fft(tx))))



% Just a test for different freq at real and iamge
% for i = 1:signal_len
%     tx_tmp2(i) = sin((2*100*pi*(i-1))/signal_len);   
% end
% tx_tmp2 = tx_tmp2.';
% 
% tx = tx_tmp + 1i * tx_tmp2;
% figure;plot(1:signal_len, 20*log10(abs(fft(tx))))



% Sampling
sampling_step = floor(wfm_freq / tx_sampling_rate * signal_len);
sampling_idx = 0;
tx = zeros(buff_size, 1);
for i = 1:buff_size
    sampling_idx = mod(sampling_idx, signal_len);
    tx(i) = signal(sampling_idx+1);
    sampling_idx = sampling_idx + sampling_step;
end

t_step = 1/tx_sampling_rate;
t = (0: t_step : (buff_size-1)*t_step)';
figure
subplot(2,2,1)
if max(t) > 1e-6 && max(t) < 1e-3
    plot(t*1e6, real(tx))
    xlabel('Time [us]')
    xlim([t(3901)*1e6, t(4001)*1e6])
elseif max(t) > 1e-3 && max(t) < 1
    plot(t*1e3, real(tx))
    xlabel('Time [ms]')
    xlim([t(3901)*1e3, t(4001)*1e3])
end
ylabel('Amp [A]')
title('Original Sine, Real part')


subplot(2,2,2)
if max(t) > 1e-6 && max(t) < 1e-3
    plot(t*1e6, real(tx))
    xlabel('Time [us]')
elseif max(t) > 1e-3 && max(t) < 1
    plot(t*1e3, real(tx))
    xlabel('Time [ms]')
end
ylabel('Amp [A]')
title('Original Sine, Real part')







%% Read data
fid = fopen('test_double_1_gain_-10.dat','r');
data = fread(fid,'*double');
fclose all;

data = reshape(data, 2, [])';
data = data(:,1)+data(:,2)*1i;

data(1:17) = [];
data(end-13:end) = [];



subplot(2,2,3)
if max(t) > 1e-6 && max(t) < 1e-3
    plot(t(1:length(data))*1e6, real(data))
    xlabel('Time [us]')
    xlim([t(3901)*1e6, t(4001)*1e6])
elseif max(t) > 1e-3 && max(t) < 1
    plot(t(1:length(data))*1e3, real(data))
    xlabel('Time [ms]')
    xlim([t(3901)*1e3, t(4001)*1e3])
end
ylabel('Amp [A]')
title('Received data, Real part')

subplot(2,2,4)
if max(t) > 1e-6 && max(t) < 1e-3
    plot(t(1:length(data))*1e6, real(data))
    xlabel('Time [us]')
elseif max(t) > 1e-3 && max(t) < 1
    plot(t(1:length(data))*1e3, real(data))
    xlabel('Time [ms]')
end
ylabel('Amp [A]')
title('Received data, Real part')



f = linspace(0, tx_sampling_rate, length(data)+1);
f(end) = [];

figure;
hold on
plot(f/1e6, 20*log10(abs(fft(data))), "LineWidth",1.5)
plot(f/1e6, 20*log10(abs(fft(real(data)))))
plot(f/1e6, 20*log10(abs(fft(imag(data)))))
xlabel('Frequency [MHz]')
ylabel('Pwr [dBm]')
title('Frequency Reponse of Received Signal')
legend('Complex', 'Real', 'Image')
grid minor


f = linspace(0, tx_sampling_rate, length(tx)+1);
f(end) = [];
figure;
hold on
plot(f/1e6, 20*log10(abs(fft(tx))), "LineWidth",1.5)
plot(f/1e6, 20*log10(abs(fft(real(tx)))))
plot(f/1e6, 20*log10(abs(fft(imag(tx)))))
xlabel('Frequency [MHz]')
ylabel('Pwr [dBm]')
title('Frequency Reponse of Sampled Original Signal')
legend('Complex', 'Real', 'Image')
grid minor





























% evaluate_folder = [directory, '\evaluate_', num2str(group_ID), '_', num2str(subgroup_ID), '_x'];
% if ~exist(evaluate_folder, 'dir')
%     mkdir(evaluate_folder)
% end
% 
% 
% N_frame = 1;
% 
% 
% % filename = [num2str(test_group), '_', file_order, '_frame_', num2str(N_frame), '_subCrIdx_250.csv'];
% filename = [num2str(group_ID), '_', num2str(subgroup_ID), '_', num2str(measurement_ID), '_frame_', num2str(N_frame), '.csv'];
% 
% 
% 
% fileID = fopen([directory, '\', filename]);
% A = textscan(fileID, '%s');
% fclose(fileID);
% 
% aa = A{1,1};
% data_char = char(aa);
% 
% clear A  aa  fileID  filename  directory
% 
% % delete the useless "(" at the beginning
% data_char(:, 1) = [];
% 
% % add the "+" sign at the beginning for positive real parts
% N_fft = size(data_char, 1);
% for i = 1:N_fft
%     if data_char(i, 1) ~= "-"
%         temp = data_char(i, :);
%         temp(end) = [];
%         temp = ['+', temp];
%         data_char(i, :) = temp;
%     end
% end
% clear temp  i
% 
% % delete the last 1 or 2 useless char(s), i.e., remove either ") " or ",)"
% if N_frame > 1
%     data_char(:, end-1:end) = [];
% else
%     data_char(:, end) = [];
% end
% 
% % transfer char string to double number
% td = zeros(N_fft, 1);
% for i = 1:N_fft
%     td(i) = str2double(data_char(i,:));
% end
% td = reshape(td, N_frame, []).';
% clear data_char
% 
% 
% 
% %% Evaluation 1, recover the COSMOS evaluation process
% fd = zeros(size(td, 1), size(td, 2));
% for i = 1:N_frame
%     fd(:, i) = fft(td(:, i));
% end
% shifted_fd = circshift(fd,N_fft/2);
% 
% % rxfd = circshift(rxfd, 512);
% 
% % Plot
% legendInfo = cell(N_frame, 1);
% 
% figure
% hold on
% for i = 1:N_frame
%     plot(-N_fft/2:N_fft/2-1, 20*log10(abs(shifted_fd(:, i))));
%     legendInfo{i} = ['frame ' num2str(i)]; 
% end
% % plot(-512:1:511, 20*log10(abs(RxSignalFreqDomain(:, 1))));
% y_min = min(mean(20*log10(abs(fd)))) - 20;
% y_max = max(max(20*log10(abs(fd)))) + 20;
% ylim([y_min, y_max])
% title(['Received Signal of Measurement ', num2str(group_ID), '\_', num2str(subgroup_ID), '\_', num2str(measurement_ID), ', COSMOS version'])
% xlabel('Subcarrier Index')
% ylabel('Magnitude [dB]')
% grid minor
% legend(legendInfo)
% 
% clear i  y_min  y_max  ans  legendInfo
% 
% 
% %% Evaluation 2
% fs = 3932.16e6/4;
% df = fs/N_fft;
% f = 0:df:(fs-df);
% figure;
% hold on
% for i = 1:N_frame
%     plot(20*log10(abs(shifted_fd(:, i))))
% end
% y_min = min(mean(20*log10(abs(fd)))) - 20;
% y_max = max(max(20*log10(abs(fd)))) + 20;
% ylim([y_min, y_max])
% title(['Received Signal of Measurement ', num2str(group_ID), '\_', num2str(subgroup_ID), '\_', num2str(measurement_ID), ', COSMOS version'])
% xlabel('Sample Index')
% ylabel('Magnitude [dB]')
% grid minor
% 
% 
% crop_range = N_fft/2 - 










