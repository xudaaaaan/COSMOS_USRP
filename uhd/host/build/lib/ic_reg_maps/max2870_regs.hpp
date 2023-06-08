/***********************************************************************
 * This file was generated by /root/uhd/host/lib/ic_reg_maps/gen_max2870_regs.py on Thu Jun  2 22:24:06 2022
 **********************************************************************/

#ifndef INCLUDED_MAX2870_REGS_HPP
#define INCLUDED_MAX2870_REGS_HPP

#include <uhd/config.hpp>
#include <uhd/exception.hpp>
#include <set>
#include <stdint.h>

class max2870_regs_t{
public:
    enum int_n_mode_t{
        INT_N_MODE_FRAC_N = 0,
        INT_N_MODE_INT_N = 1
    };
    int_n_mode_t int_n_mode;
    uint16_t int_16_bit;
    uint16_t frac_12_bit;
    enum cpoc_t{
        CPOC_DISABLED = 0,
        CPOC_ENABLED = 1
    };
    cpoc_t cpoc;
    enum cpl_t{
        CPL_DISABLED = 0,
        CPL_ENABLED = 1,
        CPL_RES1 = 2,
        CPL_RES2 = 3
    };
    cpl_t cpl;
    enum cpt_t{
        CPT_NORMAL = 0,
        CPT_RESERVED = 1,
        CPT_FORCE_SOURCE = 2,
        CPT_FORCE_SINK = 3
    };
    cpt_t cpt;
    uint16_t phase_12_bit;
    uint16_t mod_12_bit;
    enum lds_t{
        LDS_SLOW = 0,
        LDS_FAST = 1
    };
    lds_t lds;
    enum low_noise_and_spur_t{
        LOW_NOISE_AND_SPUR_LOW_NOISE = 0,
        LOW_NOISE_AND_SPUR_RESERVED = 1,
        LOW_NOISE_AND_SPUR_LOW_SPUR_1 = 2,
        LOW_NOISE_AND_SPUR_LOW_SPUR_2 = 3
    };
    low_noise_and_spur_t low_noise_and_spur;
    enum muxout_t{
        MUXOUT_TRI_STATE = 0,
        MUXOUT_HIGH = 1,
        MUXOUT_LOW = 2,
        MUXOUT_RDIV = 3,
        MUXOUT_NDIV = 4,
        MUXOUT_ALD = 5,
        MUXOUT_DLD = 6,
        MUXOUT_RES7 = 7
    };
    muxout_t muxout;
    enum reference_doubler_t{
        REFERENCE_DOUBLER_DISABLED = 0,
        REFERENCE_DOUBLER_ENABLED = 1
    };
    reference_doubler_t reference_doubler;
    enum reference_divide_by_2_t{
        REFERENCE_DIVIDE_BY_2_DISABLED = 0,
        REFERENCE_DIVIDE_BY_2_ENABLED = 1
    };
    reference_divide_by_2_t reference_divide_by_2;
    uint16_t r_counter_10_bit;
    enum double_buffer_t{
        DOUBLE_BUFFER_DISABLED = 0,
        DOUBLE_BUFFER_ENABLED = 1
    };
    double_buffer_t double_buffer;
    enum charge_pump_current_t{
        CHARGE_PUMP_CURRENT_0_32MA = 0,
        CHARGE_PUMP_CURRENT_0_64MA = 1,
        CHARGE_PUMP_CURRENT_0_96MA = 2,
        CHARGE_PUMP_CURRENT_1_28MA = 3,
        CHARGE_PUMP_CURRENT_1_60MA = 4,
        CHARGE_PUMP_CURRENT_1_92MA = 5,
        CHARGE_PUMP_CURRENT_2_24MA = 6,
        CHARGE_PUMP_CURRENT_2_56MA = 7,
        CHARGE_PUMP_CURRENT_2_88MA = 8,
        CHARGE_PUMP_CURRENT_3_20MA = 9,
        CHARGE_PUMP_CURRENT_3_52MA = 10,
        CHARGE_PUMP_CURRENT_3_84MA = 11,
        CHARGE_PUMP_CURRENT_4_16MA = 12,
        CHARGE_PUMP_CURRENT_4_48MA = 13,
        CHARGE_PUMP_CURRENT_4_80MA = 14,
        CHARGE_PUMP_CURRENT_5_12MA = 15
    };
    charge_pump_current_t charge_pump_current;
    enum ldf_t{
        LDF_FRAC_N = 0,
        LDF_INT_N = 1
    };
    ldf_t ldf;
    enum ldp_t{
        LDP_10NS = 0,
        LDP_6NS = 1
    };
    ldp_t ldp;
    enum pd_polarity_t{
        PD_POLARITY_NEGATIVE = 0,
        PD_POLARITY_POSITIVE = 1
    };
    pd_polarity_t pd_polarity;
    enum power_down_t{
        POWER_DOWN_NORMAL = 0,
        POWER_DOWN_SHUTDOWN = 1
    };
    power_down_t power_down;
    enum cp_three_state_t{
        CP_THREE_STATE_DISABLED = 0,
        CP_THREE_STATE_ENABLED = 1
    };
    cp_three_state_t cp_three_state;
    enum counter_reset_t{
        COUNTER_RESET_NORMAL = 0,
        COUNTER_RESET_RESET = 1
    };
    counter_reset_t counter_reset;
    uint8_t vco;
    enum vas_t{
        VAS_ENABLED = 0,
        VAS_DISABLED = 1
    };
    vas_t vas;
    enum retune_t{
        RETUNE_DISABLED = 0,
        RETUNE_ENABLED = 1
    };
    retune_t retune;
    enum clock_div_mode_t{
        CLOCK_DIV_MODE_CLOCK_DIVIDER_OFF = 0,
        CLOCK_DIV_MODE_FAST_LOCK = 1,
        CLOCK_DIV_MODE_PHASE = 2,
        CLOCK_DIV_MODE_RESERVED = 3
    };
    clock_div_mode_t clock_div_mode;
    uint16_t clock_divider_12_bit;
    uint8_t res4;
    uint8_t bs_msb;
    enum feedback_select_t{
        FEEDBACK_SELECT_DIVIDED = 0,
        FEEDBACK_SELECT_FUNDAMENTAL = 1
    };
    feedback_select_t feedback_select;
    enum rf_divider_select_t{
        RF_DIVIDER_SELECT_DIV1 = 0,
        RF_DIVIDER_SELECT_DIV2 = 1,
        RF_DIVIDER_SELECT_DIV4 = 2,
        RF_DIVIDER_SELECT_DIV8 = 3,
        RF_DIVIDER_SELECT_DIV16 = 4,
        RF_DIVIDER_SELECT_DIV32 = 5,
        RF_DIVIDER_SELECT_DIV64 = 6,
        RF_DIVIDER_SELECT_DIV128 = 7
    };
    rf_divider_select_t rf_divider_select;
    uint8_t band_select_clock_div;
    enum aux_output_select_t{
        AUX_OUTPUT_SELECT_DIVIDED = 0,
        AUX_OUTPUT_SELECT_FUNDAMENTAL = 1
    };
    aux_output_select_t aux_output_select;
    enum aux_output_enable_t{
        AUX_OUTPUT_ENABLE_DISABLED = 0,
        AUX_OUTPUT_ENABLE_ENABLED = 1
    };
    aux_output_enable_t aux_output_enable;
    enum aux_output_power_t{
        AUX_OUTPUT_POWER_M4DBM = 0,
        AUX_OUTPUT_POWER_M1DBM = 1,
        AUX_OUTPUT_POWER_2DBM = 2,
        AUX_OUTPUT_POWER_5DBM = 3
    };
    aux_output_power_t aux_output_power;
    enum rf_output_enable_t{
        RF_OUTPUT_ENABLE_DISABLED = 0,
        RF_OUTPUT_ENABLE_ENABLED = 1
    };
    rf_output_enable_t rf_output_enable;
    enum output_power_t{
        OUTPUT_POWER_M4DBM = 0,
        OUTPUT_POWER_M1DBM = 1,
        OUTPUT_POWER_2DBM = 2,
        OUTPUT_POWER_5DBM = 3
    };
    output_power_t output_power;
    enum f01_t{
        F01_FRAC_N = 0,
        F01_AUTO = 1
    };
    f01_t f01;
    enum ld_pin_mode_t{
        LD_PIN_MODE_LOW = 0,
        LD_PIN_MODE_DLD = 1,
        LD_PIN_MODE_ALD = 2,
        LD_PIN_MODE_HIGH = 3
    };
    ld_pin_mode_t ld_pin_mode;
    enum mux_sdo_t{
        MUX_SDO_NORMAL = 0,
        MUX_SDO_SDO = 1
    };
    mux_sdo_t mux_sdo;

    max2870_regs_t(void){
        _state = NULL;
        int_n_mode = INT_N_MODE_FRAC_N;
        int_16_bit = 125;
        frac_12_bit = 0;
        cpoc = CPOC_DISABLED;
        cpl = CPL_ENABLED;
        cpt = CPT_NORMAL;
        phase_12_bit = 1;
        mod_12_bit = 4095;
        lds = LDS_SLOW;
        low_noise_and_spur = LOW_NOISE_AND_SPUR_LOW_SPUR_2;
        muxout = MUXOUT_HIGH;
        reference_doubler = REFERENCE_DOUBLER_DISABLED;
        reference_divide_by_2 = REFERENCE_DIVIDE_BY_2_DISABLED;
        r_counter_10_bit = 1;
        double_buffer = DOUBLE_BUFFER_DISABLED;
        charge_pump_current = CHARGE_PUMP_CURRENT_2_56MA;
        ldf = LDF_FRAC_N;
        ldp = LDP_10NS;
        pd_polarity = PD_POLARITY_POSITIVE;
        power_down = POWER_DOWN_NORMAL;
        cp_three_state = CP_THREE_STATE_DISABLED;
        counter_reset = COUNTER_RESET_NORMAL;
        vco = 0;
        vas = VAS_ENABLED;
        retune = RETUNE_ENABLED;
        clock_div_mode = CLOCK_DIV_MODE_CLOCK_DIVIDER_OFF;
        clock_divider_12_bit = 1;
        res4 = 24;
        bs_msb = 0;
        feedback_select = FEEDBACK_SELECT_FUNDAMENTAL;
        rf_divider_select = RF_DIVIDER_SELECT_DIV1;
        band_select_clock_div = 0;
        aux_output_select = AUX_OUTPUT_SELECT_FUNDAMENTAL;
        aux_output_enable = AUX_OUTPUT_ENABLE_DISABLED;
        aux_output_power = AUX_OUTPUT_POWER_M4DBM;
        rf_output_enable = RF_OUTPUT_ENABLE_ENABLED;
        output_power = OUTPUT_POWER_5DBM;
        f01 = F01_AUTO;
        ld_pin_mode = LD_PIN_MODE_DLD;
        mux_sdo = MUX_SDO_NORMAL;
    }

    ~max2870_regs_t(void){
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
            reg |= (uint32_t(int_n_mode) & 0x1) << 31;
            reg |= (uint32_t(int_16_bit) & 0xffff) << 15;
            reg |= (uint32_t(frac_12_bit) & 0xfff) << 3;
            break;
        case 1:
            reg |= (uint32_t(cpoc) & 0x1) << 31;
            reg |= (uint32_t(cpl) & 0x3) << 29;
            reg |= (uint32_t(cpt) & 0x3) << 27;
            reg |= (uint32_t(phase_12_bit) & 0xfff) << 15;
            reg |= (uint32_t(mod_12_bit) & 0xfff) << 3;
            break;
        case 2:
            reg |= (uint32_t(lds) & 0x1) << 31;
            reg |= (uint32_t(low_noise_and_spur) & 0x3) << 29;
            reg |= (uint32_t(muxout) & 0x7) << 26;
            reg |= (uint32_t(reference_doubler) & 0x1) << 25;
            reg |= (uint32_t(reference_divide_by_2) & 0x1) << 24;
            reg |= (uint32_t(r_counter_10_bit) & 0x3ff) << 14;
            reg |= (uint32_t(double_buffer) & 0x1) << 13;
            reg |= (uint32_t(charge_pump_current) & 0xf) << 9;
            reg |= (uint32_t(ldf) & 0x1) << 8;
            reg |= (uint32_t(ldp) & 0x1) << 7;
            reg |= (uint32_t(pd_polarity) & 0x1) << 6;
            reg |= (uint32_t(power_down) & 0x1) << 5;
            reg |= (uint32_t(cp_three_state) & 0x1) << 4;
            reg |= (uint32_t(counter_reset) & 0x1) << 3;
            break;
        case 3:
            reg |= (uint32_t(vco) & 0x3f) << 26;
            reg |= (uint32_t(vas) & 0x1) << 25;
            reg |= (uint32_t(retune) & 0x1) << 24;
            reg |= (uint32_t(clock_div_mode) & 0x3) << 15;
            reg |= (uint32_t(clock_divider_12_bit) & 0xfff) << 3;
            break;
        case 4:
            reg |= (uint32_t(res4) & 0x3f) << 26;
            reg |= (uint32_t(bs_msb) & 0x3) << 24;
            reg |= (uint32_t(feedback_select) & 0x1) << 23;
            reg |= (uint32_t(rf_divider_select) & 0x7) << 20;
            reg |= (uint32_t(band_select_clock_div) & 0xff) << 12;
            reg |= (uint32_t(aux_output_select) & 0x1) << 9;
            reg |= (uint32_t(aux_output_enable) & 0x1) << 8;
            reg |= (uint32_t(aux_output_power) & 0x3) << 6;
            reg |= (uint32_t(rf_output_enable) & 0x1) << 5;
            reg |= (uint32_t(output_power) & 0x3) << 3;
            break;
        case 5:
            reg |= (uint32_t(f01) & 0x1) << 24;
            reg |= (uint32_t(ld_pin_mode) & 0x3) << 22;
            reg |= (uint32_t(mux_sdo) & 0x1) << 18;
            break;
        }
        return reg;
    }

    void save_state(void){
        if (_state == NULL) _state = new max2870_regs_t();
        _state->int_n_mode = this->int_n_mode;
        _state->int_16_bit = this->int_16_bit;
        _state->frac_12_bit = this->frac_12_bit;
        _state->cpoc = this->cpoc;
        _state->cpl = this->cpl;
        _state->cpt = this->cpt;
        _state->phase_12_bit = this->phase_12_bit;
        _state->mod_12_bit = this->mod_12_bit;
        _state->lds = this->lds;
        _state->low_noise_and_spur = this->low_noise_and_spur;
        _state->muxout = this->muxout;
        _state->reference_doubler = this->reference_doubler;
        _state->reference_divide_by_2 = this->reference_divide_by_2;
        _state->r_counter_10_bit = this->r_counter_10_bit;
        _state->double_buffer = this->double_buffer;
        _state->charge_pump_current = this->charge_pump_current;
        _state->ldf = this->ldf;
        _state->ldp = this->ldp;
        _state->pd_polarity = this->pd_polarity;
        _state->power_down = this->power_down;
        _state->cp_three_state = this->cp_three_state;
        _state->counter_reset = this->counter_reset;
        _state->vco = this->vco;
        _state->vas = this->vas;
        _state->retune = this->retune;
        _state->clock_div_mode = this->clock_div_mode;
        _state->clock_divider_12_bit = this->clock_divider_12_bit;
        _state->res4 = this->res4;
        _state->bs_msb = this->bs_msb;
        _state->feedback_select = this->feedback_select;
        _state->rf_divider_select = this->rf_divider_select;
        _state->band_select_clock_div = this->band_select_clock_div;
        _state->aux_output_select = this->aux_output_select;
        _state->aux_output_enable = this->aux_output_enable;
        _state->aux_output_power = this->aux_output_power;
        _state->rf_output_enable = this->rf_output_enable;
        _state->output_power = this->output_power;
        _state->f01 = this->f01;
        _state->ld_pin_mode = this->ld_pin_mode;
        _state->mux_sdo = this->mux_sdo;
    }

    template<typename T> std::set<T> get_changed_addrs(void){
        if (_state == NULL) throw uhd::runtime_error("no saved state");
        //check each register for changes
        std::set<T> addrs;
        if(_state->int_n_mode != this->int_n_mode){
            addrs.insert(0);
        }
        if(_state->int_16_bit != this->int_16_bit){
            addrs.insert(0);
        }
        if(_state->frac_12_bit != this->frac_12_bit){
            addrs.insert(0);
        }
        if(_state->cpoc != this->cpoc){
            addrs.insert(1);
        }
        if(_state->cpl != this->cpl){
            addrs.insert(1);
        }
        if(_state->cpt != this->cpt){
            addrs.insert(1);
        }
        if(_state->phase_12_bit != this->phase_12_bit){
            addrs.insert(1);
        }
        if(_state->mod_12_bit != this->mod_12_bit){
            addrs.insert(1);
        }
        if(_state->lds != this->lds){
            addrs.insert(2);
        }
        if(_state->low_noise_and_spur != this->low_noise_and_spur){
            addrs.insert(2);
        }
        if(_state->muxout != this->muxout){
            addrs.insert(2);
        }
        if(_state->reference_doubler != this->reference_doubler){
            addrs.insert(2);
        }
        if(_state->reference_divide_by_2 != this->reference_divide_by_2){
            addrs.insert(2);
        }
        if(_state->r_counter_10_bit != this->r_counter_10_bit){
            addrs.insert(2);
        }
        if(_state->double_buffer != this->double_buffer){
            addrs.insert(2);
        }
        if(_state->charge_pump_current != this->charge_pump_current){
            addrs.insert(2);
        }
        if(_state->ldf != this->ldf){
            addrs.insert(2);
        }
        if(_state->ldp != this->ldp){
            addrs.insert(2);
        }
        if(_state->pd_polarity != this->pd_polarity){
            addrs.insert(2);
        }
        if(_state->power_down != this->power_down){
            addrs.insert(2);
        }
        if(_state->cp_three_state != this->cp_three_state){
            addrs.insert(2);
        }
        if(_state->counter_reset != this->counter_reset){
            addrs.insert(2);
        }
        if(_state->vco != this->vco){
            addrs.insert(3);
        }
        if(_state->vas != this->vas){
            addrs.insert(3);
        }
        if(_state->retune != this->retune){
            addrs.insert(3);
        }
        if(_state->clock_div_mode != this->clock_div_mode){
            addrs.insert(3);
        }
        if(_state->clock_divider_12_bit != this->clock_divider_12_bit){
            addrs.insert(3);
        }
        if(_state->res4 != this->res4){
            addrs.insert(4);
        }
        if(_state->bs_msb != this->bs_msb){
            addrs.insert(4);
        }
        if(_state->feedback_select != this->feedback_select){
            addrs.insert(4);
        }
        if(_state->rf_divider_select != this->rf_divider_select){
            addrs.insert(4);
        }
        if(_state->band_select_clock_div != this->band_select_clock_div){
            addrs.insert(4);
        }
        if(_state->aux_output_select != this->aux_output_select){
            addrs.insert(4);
        }
        if(_state->aux_output_enable != this->aux_output_enable){
            addrs.insert(4);
        }
        if(_state->aux_output_power != this->aux_output_power){
            addrs.insert(4);
        }
        if(_state->rf_output_enable != this->rf_output_enable){
            addrs.insert(4);
        }
        if(_state->output_power != this->output_power){
            addrs.insert(4);
        }
        if(_state->f01 != this->f01){
            addrs.insert(5);
        }
        if(_state->ld_pin_mode != this->ld_pin_mode){
            addrs.insert(5);
        }
        if(_state->mux_sdo != this->mux_sdo){
            addrs.insert(5);
        }
        return addrs;
    }

private:
    max2870_regs_t *_state;
};

#endif /* INCLUDED_MAX2870_REGS_HPP */
