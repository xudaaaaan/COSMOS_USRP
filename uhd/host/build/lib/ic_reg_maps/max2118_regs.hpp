/***********************************************************************
 * This file was generated by /root/uhd/host/lib/ic_reg_maps/gen_max2118_regs.py on Tue Jun 13 02:10:53 2023
 **********************************************************************/

#ifndef INCLUDED_MAX2118_WRITE_REGS_HPP
#define INCLUDED_MAX2118_WRITE_REGS_HPP

#include <uhd/config.hpp>
#include <uhd/exception.hpp>
#include <set>
#include <stdint.h>

class max2118_write_regs_t{
public:
    enum div2_t{
        DIV2_DIV4 = 0,
        DIV2_DIV2 = 1
    };
    div2_t div2;
    uint8_t n_divider_msb;
    uint8_t n_divider_lsb;
    enum r_divider_t{
        R_DIVIDER_DIV2 = 0,
        R_DIVIDER_DIV4 = 1,
        R_DIVIDER_DIV8 = 2,
        R_DIVIDER_DIV16 = 3,
        R_DIVIDER_DIV32 = 4,
        R_DIVIDER_DIV64 = 5,
        R_DIVIDER_DIV128 = 6,
        R_DIVIDER_DIV256 = 7
    };
    r_divider_t r_divider;
    enum cp_current_t{
        CP_CURRENT_I_CP_50UA = 0,
        CP_CURRENT_I_CP_100UA = 1,
        CP_CURRENT_I_CP_200UA = 2,
        CP_CURRENT_I_CP_400UA = 3
    };
    cp_current_t cp_current;
    uint8_t osc_band;
    uint8_t f_dac;
    enum adl_vco_adc_latch_t{
        ADL_VCO_ADC_LATCH_DISABLED = 0,
        ADL_VCO_ADC_LATCH_ENABLED = 1
    };
    adl_vco_adc_latch_t adl_vco_adc_latch;
    enum ade_vco_ade_read_t{
        ADE_VCO_ADE_READ_DISABLED = 0,
        ADE_VCO_ADE_READ_ENABLED = 1
    };
    ade_vco_ade_read_t ade_vco_ade_read;
    enum dl_output_drive_t{
        DL_OUTPUT_DRIVE_IQ_590M_VPP = 0,
        DL_OUTPUT_DRIVE_IQ_1_VPP = 1
    };
    dl_output_drive_t dl_output_drive;
    uint8_t m_divider;
    enum diag_t{
        DIAG_NORMAL = 0,
        DIAG_CP_I_SOURCE = 1,
        DIAG_CP_I_SINK = 2,
        DIAG_CP_HIGH_Z = 3,
        DIAG_UNUSED = 4,
        DIAG_N_AND_FILT = 5,
        DIAG_R_AND_GC2 = 6,
        DIAG_M_DIV = 7
    };
    diag_t diag;
    uint8_t gc2;

    max2118_write_regs_t(void){
        _state = NULL;
        div2 = DIV2_DIV4;
        n_divider_msb = 3;
        n_divider_lsb = 182;
        r_divider = R_DIVIDER_DIV4;
        cp_current = CP_CURRENT_I_CP_400UA;
        osc_band = 5;
        f_dac = 127;
        adl_vco_adc_latch = ADL_VCO_ADC_LATCH_DISABLED;
        ade_vco_ade_read = ADE_VCO_ADE_READ_DISABLED;
        dl_output_drive = DL_OUTPUT_DRIVE_IQ_590M_VPP;
        m_divider = 2;
        diag = DIAG_NORMAL;
        gc2 = 31;
    }

    ~max2118_write_regs_t(void){
        delete _state;
    }

    uint8_t get_reg(uint8_t addr){
        uint8_t reg = 0;
        switch(addr){
        case 0:
            reg |= (uint8_t(div2) & 0x1) << 7;
            reg |= (uint8_t(n_divider_msb) & 0x7f) << 0;
            break;
        case 1:
            reg |= (uint8_t(n_divider_lsb) & 0xff) << 0;
            break;
        case 2:
            reg |= (uint8_t(r_divider) & 0x7) << 5;
            reg |= (uint8_t(cp_current) & 0x3) << 3;
            reg |= (uint8_t(osc_band) & 0x7) << 0;
            break;
        case 3:
            reg |= (uint8_t(f_dac) & 0x7f) << 0;
            break;
        case 4:
            reg |= (uint8_t(adl_vco_adc_latch) & 0x1) << 7;
            reg |= (uint8_t(ade_vco_ade_read) & 0x1) << 6;
            reg |= (uint8_t(dl_output_drive) & 0x1) << 5;
            reg |= (uint8_t(m_divider) & 0x1f) << 0;
            break;
        case 5:
            reg |= (uint8_t(diag) & 0x7) << 5;
            reg |= (uint8_t(gc2) & 0x1f) << 0;
            break;
        }
        return uint8_t(reg);
    }
    
    void set_reg(uint8_t addr, uint8_t reg){
        switch(addr){
        case 0:
            div2 = div2_t((reg >> 7) & 0x1);
            n_divider_msb = uint8_t((reg >> 0) & 0x7f);
            break;
        case 1:
            n_divider_lsb = uint8_t((reg >> 0) & 0xff);
            break;
        case 2:
            r_divider = r_divider_t((reg >> 5) & 0x7);
            cp_current = cp_current_t((reg >> 3) & 0x3);
            osc_band = uint8_t((reg >> 0) & 0x7);
            break;
        case 3:
            f_dac = uint8_t((reg >> 0) & 0x7f);
            break;
        case 4:
            adl_vco_adc_latch = adl_vco_adc_latch_t((reg >> 7) & 0x1);
            ade_vco_ade_read = ade_vco_ade_read_t((reg >> 6) & 0x1);
            dl_output_drive = dl_output_drive_t((reg >> 5) & 0x1);
            m_divider = uint8_t((reg >> 0) & 0x1f);
            break;
        case 5:
            diag = diag_t((reg >> 5) & 0x7);
            gc2 = uint8_t((reg >> 0) & 0x1f);
            break;
        }
    }

    void save_state(void){
        if (_state == NULL) _state = new max2118_write_regs_t();
        _state->div2 = this->div2;
        _state->n_divider_msb = this->n_divider_msb;
        _state->n_divider_lsb = this->n_divider_lsb;
        _state->r_divider = this->r_divider;
        _state->cp_current = this->cp_current;
        _state->osc_band = this->osc_band;
        _state->f_dac = this->f_dac;
        _state->adl_vco_adc_latch = this->adl_vco_adc_latch;
        _state->ade_vco_ade_read = this->ade_vco_ade_read;
        _state->dl_output_drive = this->dl_output_drive;
        _state->m_divider = this->m_divider;
        _state->diag = this->diag;
        _state->gc2 = this->gc2;
    }

    template<typename T> std::set<T> get_changed_addrs(void){
        if (_state == NULL) throw uhd::runtime_error("no saved state");
        //check each register for changes
        std::set<T> addrs;
        if(_state->div2 != this->div2){
            addrs.insert(0);
        }
        if(_state->n_divider_msb != this->n_divider_msb){
            addrs.insert(0);
        }
        if(_state->n_divider_lsb != this->n_divider_lsb){
            addrs.insert(1);
        }
        if(_state->r_divider != this->r_divider){
            addrs.insert(2);
        }
        if(_state->cp_current != this->cp_current){
            addrs.insert(2);
        }
        if(_state->osc_band != this->osc_band){
            addrs.insert(2);
        }
        if(_state->f_dac != this->f_dac){
            addrs.insert(3);
        }
        if(_state->adl_vco_adc_latch != this->adl_vco_adc_latch){
            addrs.insert(4);
        }
        if(_state->ade_vco_ade_read != this->ade_vco_ade_read){
            addrs.insert(4);
        }
        if(_state->dl_output_drive != this->dl_output_drive){
            addrs.insert(4);
        }
        if(_state->m_divider != this->m_divider){
            addrs.insert(4);
        }
        if(_state->diag != this->diag){
            addrs.insert(5);
        }
        if(_state->gc2 != this->gc2){
            addrs.insert(5);
        }
        return addrs;
    }

    uint16_t get_n_divider(void){
        return 
        (uint16_t(n_divider_lsb & 0xff) << 0) |
        (uint16_t(n_divider_msb & 0x7f) << 8) |
        0;
    }

    void set_n_divider(uint16_t reg){
        n_divider_lsb = (reg >> 0) & 0xff;
        n_divider_msb = (reg >> 8) & 0x7f;
    }

private:
    max2118_write_regs_t *_state;
};

#endif /* INCLUDED_MAX2118_WRITE_REGS_HPP */
/***********************************************************************
 * This file was generated by /root/uhd/host/lib/ic_reg_maps/gen_max2118_regs.py on Tue Jun 13 02:10:53 2023
 **********************************************************************/

#ifndef INCLUDED_MAX2118_READ_REGS_HPP
#define INCLUDED_MAX2118_READ_REGS_HPP

#include <uhd/config.hpp>
#include <uhd/exception.hpp>
#include <set>
#include <stdint.h>

class max2118_read_regs_t{
public:
    enum pwr_t{
        PWR_NOT_RESET = 0,
        PWR_RESET = 1
    };
    pwr_t pwr;
    uint8_t adc;
    uint8_t filter_dac;

    max2118_read_regs_t(void){
        _state = NULL;
        pwr = PWR_NOT_RESET;
        adc = 0;
        filter_dac = 0;
    }

    ~max2118_read_regs_t(void){
        delete _state;
    }

    uint8_t get_reg(uint8_t addr){
        uint8_t reg = 0;
        switch(addr){
        case 0:
            reg |= (uint8_t(pwr) & 0x1) << 6;
            reg |= (uint8_t(adc) & 0x7) << 2;
            break;
        case 1:
            reg |= (uint8_t(filter_dac) & 0x7f) << 0;
            break;
        }
        return uint8_t(reg);
    }
    
    void set_reg(uint8_t addr, uint8_t reg){
        switch(addr){
        case 0:
            pwr = pwr_t((reg >> 6) & 0x1);
            adc = uint8_t((reg >> 2) & 0x7);
            break;
        case 1:
            filter_dac = uint8_t((reg >> 0) & 0x7f);
            break;
        }
    }

    void save_state(void){
        if (_state == NULL) _state = new max2118_read_regs_t();
        _state->pwr = this->pwr;
        _state->adc = this->adc;
        _state->filter_dac = this->filter_dac;
    }

    template<typename T> std::set<T> get_changed_addrs(void){
        if (_state == NULL) throw uhd::runtime_error("no saved state");
        //check each register for changes
        std::set<T> addrs;
        if(_state->pwr != this->pwr){
            addrs.insert(0);
        }
        if(_state->adc != this->adc){
            addrs.insert(0);
        }
        if(_state->filter_dac != this->filter_dac){
            addrs.insert(1);
        }
        return addrs;
    }

private:
    max2118_read_regs_t *_state;
};

#endif /* INCLUDED_MAX2118_READ_REGS_HPP */
