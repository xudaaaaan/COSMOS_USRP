/***********************************************************************
 * This file was generated by /root/uhd/host/lib/ic_reg_maps/gen_ads62p48_regs.py on Tue Jun 13 02:16:45 2023
 **********************************************************************/

#ifndef INCLUDED_ADS62P48_REGS_HPP
#define INCLUDED_ADS62P48_REGS_HPP

#include <uhd/config.hpp>
#include <uhd/exception.hpp>
#include <set>
#include <stdint.h>

class ads62p48_regs_t{
public:
    uint8_t reset;
    uint8_t serial_readout;
    uint8_t enable_low_speed_mode;
    enum ref_t{
        REF_INTERNAL = 0,
        REF_EXTERNAL = 3
    };
    ref_t ref;
    enum standby_t{
        STANDBY_NORMAL = 0,
        STANDBY_STANDBY = 1
    };
    standby_t standby;
    enum power_down_t{
        POWER_DOWN_PINS = 0,
        POWER_DOWN_NORMAL = 8,
        POWER_DOWN_CHB = 9,
        POWER_DOWN_CHA = 10,
        POWER_DOWN_CHAB = 11,
        POWER_DOWN_GLOBAL = 12,
        POWER_DOWN_CHB_STANDBY = 13,
        POWER_DOWN_CHA_STANDBY = 14,
        POWER_DOWN_MUX = 15
    };
    power_down_t power_down;
    enum lvds_cmos_t{
        LVDS_CMOS_PARALLEL_CMOS = 0,
        LVDS_CMOS_DDR_LVDS = 1
    };
    lvds_cmos_t lvds_cmos;
    enum clk_out_pos_edge_t{
        CLK_OUT_POS_EDGE_NORMAL = 0,
        CLK_OUT_POS_EDGE_PLUS4_26 = 5,
        CLK_OUT_POS_EDGE_MINUS4_26 = 7,
        CLK_OUT_POS_EDGE_MINUS7_26 = 6
    };
    clk_out_pos_edge_t clk_out_pos_edge;
    enum clk_out_neg_edge_t{
        CLK_OUT_NEG_EDGE_NORMAL = 0,
        CLK_OUT_NEG_EDGE_PLUS4_26 = 5,
        CLK_OUT_NEG_EDGE_MINUS4_26 = 7,
        CLK_OUT_NEG_EDGE_MINUS7_26 = 6
    };
    clk_out_neg_edge_t clk_out_neg_edge;
    enum channel_control_t{
        CHANNEL_CONTROL_COMMON = 0,
        CHANNEL_CONTROL_INDEPENDENT = 1
    };
    channel_control_t channel_control;
    enum data_format_t{
        DATA_FORMAT_2S_COMPLIMENT = 2,
        DATA_FORMAT_OFFSET_BINARY = 3
    };
    data_format_t data_format;
    uint8_t custom_pattern_low;
    uint8_t custom_pattern_high;
    uint8_t enable_offset_corr_chA;
    uint8_t gain_chA;
    uint8_t offset_corr_time_const_chA;
    uint8_t fine_gain_adjust_chA;
    enum test_patterns_chA_t{
        TEST_PATTERNS_CHA_NORMAL = 0,
        TEST_PATTERNS_CHA_ZEROS = 1,
        TEST_PATTERNS_CHA_ONES = 2,
        TEST_PATTERNS_CHA_TOGGLE = 3,
        TEST_PATTERNS_CHA_RAMP = 4,
        TEST_PATTERNS_CHA_CUSTOM = 5
    };
    test_patterns_chA_t test_patterns_chA;
    uint8_t offset_pedestal_chA;
    uint8_t enable_offset_corr_chB;
    uint8_t gain_chB;
    uint8_t offset_corr_time_const_chB;
    uint8_t fine_gain_adjust_chB;
    enum test_patterns_chB_t{
        TEST_PATTERNS_CHB_NORMAL = 0,
        TEST_PATTERNS_CHB_ZEROS = 1,
        TEST_PATTERNS_CHB_ONES = 2,
        TEST_PATTERNS_CHB_TOGGLE = 3,
        TEST_PATTERNS_CHB_RAMP = 4,
        TEST_PATTERNS_CHB_CUSTOM = 5
    };
    test_patterns_chB_t test_patterns_chB;
    uint8_t offset_pedestal_chB;

    ads62p48_regs_t(void){
        _state = NULL;
        reset = 0;
        serial_readout = 0;
        enable_low_speed_mode = 0;
        ref = REF_INTERNAL;
        standby = STANDBY_NORMAL;
        power_down = POWER_DOWN_PINS;
        lvds_cmos = LVDS_CMOS_PARALLEL_CMOS;
        clk_out_pos_edge = CLK_OUT_POS_EDGE_NORMAL;
        clk_out_neg_edge = CLK_OUT_NEG_EDGE_NORMAL;
        channel_control = CHANNEL_CONTROL_COMMON;
        data_format = DATA_FORMAT_2S_COMPLIMENT;
        custom_pattern_low = 0;
        custom_pattern_high = 0;
        enable_offset_corr_chA = 0;
        gain_chA = 0;
        offset_corr_time_const_chA = 0;
        fine_gain_adjust_chA = 0;
        test_patterns_chA = TEST_PATTERNS_CHA_NORMAL;
        offset_pedestal_chA = 0;
        enable_offset_corr_chB = 0;
        gain_chB = 0;
        offset_corr_time_const_chB = 0;
        fine_gain_adjust_chB = 0;
        test_patterns_chB = TEST_PATTERNS_CHB_NORMAL;
        offset_pedestal_chB = 0;
    }

    ~ads62p48_regs_t(void){
        delete _state;
    }

    uint8_t get_reg(uint8_t addr){
        uint8_t reg = 0;
        switch(addr){
        case 0:
            reg |= (uint8_t(reset) & 0x1) << 7;
            reg |= (uint8_t(serial_readout) & 0x1) << 0;
            break;
        case 32:
            reg |= (uint8_t(enable_low_speed_mode) & 0x1) << 2;
            break;
        case 63:
            reg |= (uint8_t(ref) & 0x3) << 5;
            reg |= (uint8_t(standby) & 0x1) << 1;
            break;
        case 64:
            reg |= (uint8_t(power_down) & 0xf) << 0;
            break;
        case 65:
            reg |= (uint8_t(lvds_cmos) & 0x1) << 7;
            break;
        case 68:
            reg |= (uint8_t(clk_out_pos_edge) & 0x7) << 5;
            reg |= (uint8_t(clk_out_neg_edge) & 0x7) << 2;
            break;
        case 80:
            reg |= (uint8_t(channel_control) & 0x1) << 6;
            reg |= (uint8_t(data_format) & 0x3) << 1;
            break;
        case 81:
            reg |= (uint8_t(custom_pattern_low) & 0xff) << 0;
            break;
        case 82:
            reg |= (uint8_t(custom_pattern_high) & 0x3f) << 0;
            break;
        case 83:
            reg |= (uint8_t(enable_offset_corr_chA) & 0x1) << 6;
            break;
        case 85:
            reg |= (uint8_t(gain_chA) & 0xf) << 4;
            reg |= (uint8_t(offset_corr_time_const_chA) & 0xf) << 0;
            break;
        case 87:
            reg |= (uint8_t(fine_gain_adjust_chA) & 0x7f) << 0;
            break;
        case 98:
            reg |= (uint8_t(test_patterns_chA) & 0x7) << 0;
            break;
        case 99:
            reg |= (uint8_t(offset_pedestal_chA) & 0x3f) << 0;
            break;
        case 102:
            reg |= (uint8_t(enable_offset_corr_chB) & 0x1) << 6;
            break;
        case 104:
            reg |= (uint8_t(gain_chB) & 0xf) << 4;
            reg |= (uint8_t(offset_corr_time_const_chB) & 0xf) << 0;
            break;
        case 106:
            reg |= (uint8_t(fine_gain_adjust_chB) & 0x7f) << 0;
            break;
        case 117:
            reg |= (uint8_t(test_patterns_chB) & 0x7) << 0;
            break;
        case 118:
            reg |= (uint8_t(offset_pedestal_chB) & 0x3f) << 0;
            break;
        }
        return reg;
    }
    
    uint16_t get_write_reg(uint8_t addr){
        return (uint16_t(addr) << 8) | get_reg(addr);
    }
    
    uint16_t get_read_reg(uint8_t addr){
        return (uint16_t(addr) << 8) | (1 << 7);
    }

    void save_state(void){
        if (_state == NULL) _state = new ads62p48_regs_t();
        _state->reset = this->reset;
        _state->serial_readout = this->serial_readout;
        _state->enable_low_speed_mode = this->enable_low_speed_mode;
        _state->ref = this->ref;
        _state->standby = this->standby;
        _state->power_down = this->power_down;
        _state->lvds_cmos = this->lvds_cmos;
        _state->clk_out_pos_edge = this->clk_out_pos_edge;
        _state->clk_out_neg_edge = this->clk_out_neg_edge;
        _state->channel_control = this->channel_control;
        _state->data_format = this->data_format;
        _state->custom_pattern_low = this->custom_pattern_low;
        _state->custom_pattern_high = this->custom_pattern_high;
        _state->enable_offset_corr_chA = this->enable_offset_corr_chA;
        _state->gain_chA = this->gain_chA;
        _state->offset_corr_time_const_chA = this->offset_corr_time_const_chA;
        _state->fine_gain_adjust_chA = this->fine_gain_adjust_chA;
        _state->test_patterns_chA = this->test_patterns_chA;
        _state->offset_pedestal_chA = this->offset_pedestal_chA;
        _state->enable_offset_corr_chB = this->enable_offset_corr_chB;
        _state->gain_chB = this->gain_chB;
        _state->offset_corr_time_const_chB = this->offset_corr_time_const_chB;
        _state->fine_gain_adjust_chB = this->fine_gain_adjust_chB;
        _state->test_patterns_chB = this->test_patterns_chB;
        _state->offset_pedestal_chB = this->offset_pedestal_chB;
    }

    template<typename T> std::set<T> get_changed_addrs(void){
        if (_state == NULL) throw uhd::runtime_error("no saved state");
        //check each register for changes
        std::set<T> addrs;
        if(_state->reset != this->reset){
            addrs.insert(0);
        }
        if(_state->serial_readout != this->serial_readout){
            addrs.insert(0);
        }
        if(_state->enable_low_speed_mode != this->enable_low_speed_mode){
            addrs.insert(32);
        }
        if(_state->ref != this->ref){
            addrs.insert(63);
        }
        if(_state->standby != this->standby){
            addrs.insert(63);
        }
        if(_state->power_down != this->power_down){
            addrs.insert(64);
        }
        if(_state->lvds_cmos != this->lvds_cmos){
            addrs.insert(65);
        }
        if(_state->clk_out_pos_edge != this->clk_out_pos_edge){
            addrs.insert(68);
        }
        if(_state->clk_out_neg_edge != this->clk_out_neg_edge){
            addrs.insert(68);
        }
        if(_state->channel_control != this->channel_control){
            addrs.insert(80);
        }
        if(_state->data_format != this->data_format){
            addrs.insert(80);
        }
        if(_state->custom_pattern_low != this->custom_pattern_low){
            addrs.insert(81);
        }
        if(_state->custom_pattern_high != this->custom_pattern_high){
            addrs.insert(82);
        }
        if(_state->enable_offset_corr_chA != this->enable_offset_corr_chA){
            addrs.insert(83);
        }
        if(_state->gain_chA != this->gain_chA){
            addrs.insert(85);
        }
        if(_state->offset_corr_time_const_chA != this->offset_corr_time_const_chA){
            addrs.insert(85);
        }
        if(_state->fine_gain_adjust_chA != this->fine_gain_adjust_chA){
            addrs.insert(87);
        }
        if(_state->test_patterns_chA != this->test_patterns_chA){
            addrs.insert(98);
        }
        if(_state->offset_pedestal_chA != this->offset_pedestal_chA){
            addrs.insert(99);
        }
        if(_state->enable_offset_corr_chB != this->enable_offset_corr_chB){
            addrs.insert(102);
        }
        if(_state->gain_chB != this->gain_chB){
            addrs.insert(104);
        }
        if(_state->offset_corr_time_const_chB != this->offset_corr_time_const_chB){
            addrs.insert(104);
        }
        if(_state->fine_gain_adjust_chB != this->fine_gain_adjust_chB){
            addrs.insert(106);
        }
        if(_state->test_patterns_chB != this->test_patterns_chB){
            addrs.insert(117);
        }
        if(_state->offset_pedestal_chB != this->offset_pedestal_chB){
            addrs.insert(118);
        }
        return addrs;
    }

private:
    ads62p48_regs_t *_state;
};

#endif /* INCLUDED_ADS62P48_REGS_HPP */
