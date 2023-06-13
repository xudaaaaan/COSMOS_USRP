/***********************************************************************
 * This file was generated by /root/uhd/host/lib/ic_reg_maps/gen_adf4350_regs.py on Tue Jun 13 02:10:05 2023
 **********************************************************************/

#ifndef INCLUDED_ADF4350_REGS_HPP
#define INCLUDED_ADF4350_REGS_HPP

#include <uhd/config.hpp>
#include <uhd/exception.hpp>
#include <set>
#include <stdint.h>

class adf4350_regs_t{
public:
    uint16_t frac_12_bit;
    uint16_t int_16_bit;
    uint16_t mod_12_bit;
    uint16_t phase_12_bit;
    enum prescaler_t{
        PRESCALER_4_5 = 0,
        PRESCALER_8_9 = 1
    };
    prescaler_t prescaler;
    enum counter_reset_t{
        COUNTER_RESET_DISABLED = 0,
        COUNTER_RESET_ENABLED = 1
    };
    counter_reset_t counter_reset;
    enum cp_three_state_t{
        CP_THREE_STATE_DISABLED = 0,
        CP_THREE_STATE_ENABLED = 1
    };
    cp_three_state_t cp_three_state;
    enum power_down_t{
        POWER_DOWN_DISABLED = 0,
        POWER_DOWN_ENABLED = 1
    };
    power_down_t power_down;
    enum pd_polarity_t{
        PD_POLARITY_NEGATIVE = 0,
        PD_POLARITY_POSITIVE = 1
    };
    pd_polarity_t pd_polarity;
    enum ldp_t{
        LDP_10NS = 0,
        LDP_6NS = 1
    };
    ldp_t ldp;
    enum ldf_t{
        LDF_FRAC_N = 0,
        LDF_INT_N = 1
    };
    ldf_t ldf;
    enum charge_pump_current_t{
        CHARGE_PUMP_CURRENT_0_31MA = 0,
        CHARGE_PUMP_CURRENT_0_63MA = 1,
        CHARGE_PUMP_CURRENT_0_94MA = 2,
        CHARGE_PUMP_CURRENT_1_25MA = 3,
        CHARGE_PUMP_CURRENT_1_56MA = 4,
        CHARGE_PUMP_CURRENT_1_88MA = 5,
        CHARGE_PUMP_CURRENT_2_19MA = 6,
        CHARGE_PUMP_CURRENT_2_50MA = 7,
        CHARGE_PUMP_CURRENT_2_81MA = 8,
        CHARGE_PUMP_CURRENT_3_13MA = 9,
        CHARGE_PUMP_CURRENT_3_44MA = 10,
        CHARGE_PUMP_CURRENT_3_75MA = 11,
        CHARGE_PUMP_CURRENT_4_07MA = 12,
        CHARGE_PUMP_CURRENT_4_38MA = 13,
        CHARGE_PUMP_CURRENT_4_69MA = 14,
        CHARGE_PUMP_CURRENT_5_00MA = 15
    };
    charge_pump_current_t charge_pump_current;
    enum double_buffer_t{
        DOUBLE_BUFFER_DISABLED = 0,
        DOUBLE_BUFFER_ENABLED = 1
    };
    double_buffer_t double_buffer;
    uint16_t r_counter_10_bit;
    enum reference_divide_by_2_t{
        REFERENCE_DIVIDE_BY_2_DISABLED = 0,
        REFERENCE_DIVIDE_BY_2_ENABLED = 1
    };
    reference_divide_by_2_t reference_divide_by_2;
    enum reference_doubler_t{
        REFERENCE_DOUBLER_DISABLED = 0,
        REFERENCE_DOUBLER_ENABLED = 1
    };
    reference_doubler_t reference_doubler;
    enum muxout_t{
        MUXOUT_3STATE = 0,
        MUXOUT_DVDD = 1,
        MUXOUT_DGND = 2,
        MUXOUT_RDIV = 3,
        MUXOUT_NDIV = 4,
        MUXOUT_ANALOG_LD = 5,
        MUXOUT_DLD = 6,
        MUXOUT_RESERVED = 7
    };
    muxout_t muxout;
    enum low_noise_and_spur_t{
        LOW_NOISE_AND_SPUR_LOW_NOISE = 0,
        LOW_NOISE_AND_SPUR_RESERVED0 = 1,
        LOW_NOISE_AND_SPUR_RESERVED1 = 2,
        LOW_NOISE_AND_SPUR_LOW_SPUR = 3
    };
    low_noise_and_spur_t low_noise_and_spur;
    uint16_t clock_divider_12_bit;
    enum clock_div_mode_t{
        CLOCK_DIV_MODE_CLOCK_DIVIDER_OFF = 0,
        CLOCK_DIV_MODE_FAST_LOCK = 1,
        CLOCK_DIV_MODE_RESYNC_ENABLE = 2,
        CLOCK_DIV_MODE_RESERVED = 3
    };
    clock_div_mode_t clock_div_mode;
    enum cycle_slip_reduction_t{
        CYCLE_SLIP_REDUCTION_DISABLED = 0,
        CYCLE_SLIP_REDUCTION_ENABLED = 1
    };
    cycle_slip_reduction_t cycle_slip_reduction;
    enum output_power_t{
        OUTPUT_POWER_M4DBM = 0,
        OUTPUT_POWER_M1DBM = 1,
        OUTPUT_POWER_2DBM = 2,
        OUTPUT_POWER_5DBM = 3
    };
    output_power_t output_power;
    enum rf_output_enable_t{
        RF_OUTPUT_ENABLE_DISABLED = 0,
        RF_OUTPUT_ENABLE_ENABLED = 1
    };
    rf_output_enable_t rf_output_enable;
    enum aux_output_power_t{
        AUX_OUTPUT_POWER_M4DBM = 0,
        AUX_OUTPUT_POWER_M1DBM = 1,
        AUX_OUTPUT_POWER_2DBM = 2,
        AUX_OUTPUT_POWER_5DBM = 3
    };
    aux_output_power_t aux_output_power;
    enum aux_output_enable_t{
        AUX_OUTPUT_ENABLE_DISABLED = 0,
        AUX_OUTPUT_ENABLE_ENABLED = 1
    };
    aux_output_enable_t aux_output_enable;
    enum aux_output_select_t{
        AUX_OUTPUT_SELECT_DIVIDED = 0,
        AUX_OUTPUT_SELECT_FUNDAMENTAL = 1
    };
    aux_output_select_t aux_output_select;
    enum mute_till_lock_detect_t{
        MUTE_TILL_LOCK_DETECT_MUTE_DISABLED = 0,
        MUTE_TILL_LOCK_DETECT_MUTE_ENABLED = 1
    };
    mute_till_lock_detect_t mute_till_lock_detect;
    enum vco_power_down_t{
        VCO_POWER_DOWN_VCO_POWERED_UP = 0,
        VCO_POWER_DOWN_VCO_POWERED_DOWN = 1
    };
    vco_power_down_t vco_power_down;
    uint8_t band_select_clock_div;
    enum rf_divider_select_t{
        RF_DIVIDER_SELECT_DIV1 = 0,
        RF_DIVIDER_SELECT_DIV2 = 1,
        RF_DIVIDER_SELECT_DIV4 = 2,
        RF_DIVIDER_SELECT_DIV8 = 3,
        RF_DIVIDER_SELECT_DIV16 = 4
    };
    rf_divider_select_t rf_divider_select;
    enum feedback_select_t{
        FEEDBACK_SELECT_DIVIDED = 0,
        FEEDBACK_SELECT_FUNDAMENTAL = 1
    };
    feedback_select_t feedback_select;
    enum ld_pin_mode_t{
        LD_PIN_MODE_LOW0 = 0,
        LD_PIN_MODE_DLD = 1,
        LD_PIN_MODE_LOW = 2,
        LD_PIN_MODE_HIGH = 3
    };
    ld_pin_mode_t ld_pin_mode;

    adf4350_regs_t(void){
        _state = NULL;
        frac_12_bit = 0;
        int_16_bit = 35;
        mod_12_bit = 4095;
        phase_12_bit = 0;
        prescaler = PRESCALER_4_5;
        counter_reset = COUNTER_RESET_DISABLED;
        cp_three_state = CP_THREE_STATE_DISABLED;
        power_down = POWER_DOWN_DISABLED;
        pd_polarity = PD_POLARITY_POSITIVE;
        ldp = LDP_10NS;
        ldf = LDF_FRAC_N;
        charge_pump_current = CHARGE_PUMP_CURRENT_1_88MA;
        double_buffer = DOUBLE_BUFFER_DISABLED;
        r_counter_10_bit = 0;
        reference_divide_by_2 = REFERENCE_DIVIDE_BY_2_ENABLED;
        reference_doubler = REFERENCE_DOUBLER_DISABLED;
        muxout = MUXOUT_DVDD;
        low_noise_and_spur = LOW_NOISE_AND_SPUR_LOW_SPUR;
        clock_divider_12_bit = 0;
        clock_div_mode = CLOCK_DIV_MODE_FAST_LOCK;
        cycle_slip_reduction = CYCLE_SLIP_REDUCTION_DISABLED;
        output_power = OUTPUT_POWER_5DBM;
        rf_output_enable = RF_OUTPUT_ENABLE_ENABLED;
        aux_output_power = AUX_OUTPUT_POWER_M4DBM;
        aux_output_enable = AUX_OUTPUT_ENABLE_DISABLED;
        aux_output_select = AUX_OUTPUT_SELECT_FUNDAMENTAL;
        mute_till_lock_detect = MUTE_TILL_LOCK_DETECT_MUTE_DISABLED;
        vco_power_down = VCO_POWER_DOWN_VCO_POWERED_UP;
        band_select_clock_div = 0;
        rf_divider_select = RF_DIVIDER_SELECT_DIV1;
        feedback_select = FEEDBACK_SELECT_FUNDAMENTAL;
        ld_pin_mode = LD_PIN_MODE_DLD;
    }

    ~adf4350_regs_t(void){
        delete _state;
    }

    enum addr_t{
        ADDR_R0 = 0,
        ADDR_R1 = 1,
        ADDR_R2 = 2,
        ADDR_R3 = 3,
        ADDR_R4 = 4,
        ADDR_R5 = 5
    };
    
    uint32_t get_reg(uint8_t addr){
        uint32_t reg = addr & 0x7;
        switch(addr){
        case 0:
            reg |= (uint32_t(frac_12_bit) & 0xfff) << 3;
            reg |= (uint32_t(int_16_bit) & 0xffff) << 15;
            break;
        case 1:
            reg |= (uint32_t(mod_12_bit) & 0xfff) << 3;
            reg |= (uint32_t(phase_12_bit) & 0xfff) << 15;
            reg |= (uint32_t(prescaler) & 0x1) << 27;
            break;
        case 2:
            reg |= (uint32_t(counter_reset) & 0x1) << 3;
            reg |= (uint32_t(cp_three_state) & 0x1) << 4;
            reg |= (uint32_t(power_down) & 0x1) << 5;
            reg |= (uint32_t(pd_polarity) & 0x1) << 6;
            reg |= (uint32_t(ldp) & 0x1) << 7;
            reg |= (uint32_t(ldf) & 0x1) << 8;
            reg |= (uint32_t(charge_pump_current) & 0xf) << 9;
            reg |= (uint32_t(double_buffer) & 0x1) << 13;
            reg |= (uint32_t(r_counter_10_bit) & 0x3ff) << 14;
            reg |= (uint32_t(reference_divide_by_2) & 0x1) << 24;
            reg |= (uint32_t(reference_doubler) & 0x1) << 25;
            reg |= (uint32_t(muxout) & 0x7) << 26;
            reg |= (uint32_t(low_noise_and_spur) & 0x3) << 29;
            break;
        case 3:
            reg |= (uint32_t(clock_divider_12_bit) & 0xfff) << 3;
            reg |= (uint32_t(clock_div_mode) & 0x3) << 15;
            reg |= (uint32_t(cycle_slip_reduction) & 0x1) << 18;
            break;
        case 4:
            reg |= (uint32_t(output_power) & 0x3) << 3;
            reg |= (uint32_t(rf_output_enable) & 0x1) << 5;
            reg |= (uint32_t(aux_output_power) & 0x3) << 6;
            reg |= (uint32_t(aux_output_enable) & 0x1) << 8;
            reg |= (uint32_t(aux_output_select) & 0x1) << 9;
            reg |= (uint32_t(mute_till_lock_detect) & 0x1) << 10;
            reg |= (uint32_t(vco_power_down) & 0x1) << 11;
            reg |= (uint32_t(band_select_clock_div) & 0xff) << 12;
            reg |= (uint32_t(rf_divider_select) & 0x7) << 20;
            reg |= (uint32_t(feedback_select) & 0x1) << 23;
            break;
        case 5:
            reg |= (uint32_t(ld_pin_mode) & 0x3) << 22;
            break;
        }
        return reg;
    }

    void save_state(void){
        if (_state == NULL) _state = new adf4350_regs_t();
        _state->frac_12_bit = this->frac_12_bit;
        _state->int_16_bit = this->int_16_bit;
        _state->mod_12_bit = this->mod_12_bit;
        _state->phase_12_bit = this->phase_12_bit;
        _state->prescaler = this->prescaler;
        _state->counter_reset = this->counter_reset;
        _state->cp_three_state = this->cp_three_state;
        _state->power_down = this->power_down;
        _state->pd_polarity = this->pd_polarity;
        _state->ldp = this->ldp;
        _state->ldf = this->ldf;
        _state->charge_pump_current = this->charge_pump_current;
        _state->double_buffer = this->double_buffer;
        _state->r_counter_10_bit = this->r_counter_10_bit;
        _state->reference_divide_by_2 = this->reference_divide_by_2;
        _state->reference_doubler = this->reference_doubler;
        _state->muxout = this->muxout;
        _state->low_noise_and_spur = this->low_noise_and_spur;
        _state->clock_divider_12_bit = this->clock_divider_12_bit;
        _state->clock_div_mode = this->clock_div_mode;
        _state->cycle_slip_reduction = this->cycle_slip_reduction;
        _state->output_power = this->output_power;
        _state->rf_output_enable = this->rf_output_enable;
        _state->aux_output_power = this->aux_output_power;
        _state->aux_output_enable = this->aux_output_enable;
        _state->aux_output_select = this->aux_output_select;
        _state->mute_till_lock_detect = this->mute_till_lock_detect;
        _state->vco_power_down = this->vco_power_down;
        _state->band_select_clock_div = this->band_select_clock_div;
        _state->rf_divider_select = this->rf_divider_select;
        _state->feedback_select = this->feedback_select;
        _state->ld_pin_mode = this->ld_pin_mode;
    }

    template<typename T> std::set<T> get_changed_addrs(void){
        if (_state == NULL) throw uhd::runtime_error("no saved state");
        //check each register for changes
        std::set<T> addrs;
        if(_state->frac_12_bit != this->frac_12_bit){
            addrs.insert(0);
        }
        if(_state->int_16_bit != this->int_16_bit){
            addrs.insert(0);
        }
        if(_state->mod_12_bit != this->mod_12_bit){
            addrs.insert(1);
        }
        if(_state->phase_12_bit != this->phase_12_bit){
            addrs.insert(1);
        }
        if(_state->prescaler != this->prescaler){
            addrs.insert(1);
        }
        if(_state->counter_reset != this->counter_reset){
            addrs.insert(2);
        }
        if(_state->cp_three_state != this->cp_three_state){
            addrs.insert(2);
        }
        if(_state->power_down != this->power_down){
            addrs.insert(2);
        }
        if(_state->pd_polarity != this->pd_polarity){
            addrs.insert(2);
        }
        if(_state->ldp != this->ldp){
            addrs.insert(2);
        }
        if(_state->ldf != this->ldf){
            addrs.insert(2);
        }
        if(_state->charge_pump_current != this->charge_pump_current){
            addrs.insert(2);
        }
        if(_state->double_buffer != this->double_buffer){
            addrs.insert(2);
        }
        if(_state->r_counter_10_bit != this->r_counter_10_bit){
            addrs.insert(2);
        }
        if(_state->reference_divide_by_2 != this->reference_divide_by_2){
            addrs.insert(2);
        }
        if(_state->reference_doubler != this->reference_doubler){
            addrs.insert(2);
        }
        if(_state->muxout != this->muxout){
            addrs.insert(2);
        }
        if(_state->low_noise_and_spur != this->low_noise_and_spur){
            addrs.insert(2);
        }
        if(_state->clock_divider_12_bit != this->clock_divider_12_bit){
            addrs.insert(3);
        }
        if(_state->clock_div_mode != this->clock_div_mode){
            addrs.insert(3);
        }
        if(_state->cycle_slip_reduction != this->cycle_slip_reduction){
            addrs.insert(3);
        }
        if(_state->output_power != this->output_power){
            addrs.insert(4);
        }
        if(_state->rf_output_enable != this->rf_output_enable){
            addrs.insert(4);
        }
        if(_state->aux_output_power != this->aux_output_power){
            addrs.insert(4);
        }
        if(_state->aux_output_enable != this->aux_output_enable){
            addrs.insert(4);
        }
        if(_state->aux_output_select != this->aux_output_select){
            addrs.insert(4);
        }
        if(_state->mute_till_lock_detect != this->mute_till_lock_detect){
            addrs.insert(4);
        }
        if(_state->vco_power_down != this->vco_power_down){
            addrs.insert(4);
        }
        if(_state->band_select_clock_div != this->band_select_clock_div){
            addrs.insert(4);
        }
        if(_state->rf_divider_select != this->rf_divider_select){
            addrs.insert(4);
        }
        if(_state->feedback_select != this->feedback_select){
            addrs.insert(4);
        }
        if(_state->ld_pin_mode != this->ld_pin_mode){
            addrs.insert(5);
        }
        return addrs;
    }

private:
    adf4350_regs_t *_state;
};

#endif /* INCLUDED_ADF4350_REGS_HPP */
