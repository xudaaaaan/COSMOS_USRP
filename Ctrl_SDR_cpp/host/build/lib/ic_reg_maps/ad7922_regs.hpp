/***********************************************************************
 * This file was generated by /root/uhd/host/lib/ic_reg_maps/gen_ad7922_regs.py on Thu Jun  2 22:24:07 2022
 **********************************************************************/

#ifndef INCLUDED_AD7922_REGS_HPP
#define INCLUDED_AD7922_REGS_HPP

#include <uhd/config.hpp>
#include <uhd/exception.hpp>
#include <set>
#include <stdint.h>

class ad7922_regs_t{
public:
    uint16_t result;
    uint8_t mod;
    uint8_t chn;

    ad7922_regs_t(void){
        _state = NULL;
        result = 0;
        mod = 0;
        chn = 0;
    }

    ~ad7922_regs_t(void){
        delete _state;
    }

    uint16_t get_reg(void){
        uint16_t reg = 0;
        reg |= (uint32_t(result) & 0xfff) << 0;
        reg |= (uint32_t(mod) & 0x1) << 12;
        reg |= (uint32_t(chn) & 0x1) << 13;
        return reg;
    }
    
    void set_reg(uint16_t reg){
        result = uint16_t((reg >> 0) & 0xfff);
        mod = uint8_t((reg >> 12) & 0x1);
        chn = uint8_t((reg >> 13) & 0x1);
    }

    void save_state(void){
        if (_state == NULL) _state = new ad7922_regs_t();
        _state->result = this->result;
        _state->mod = this->mod;
        _state->chn = this->chn;
    }

    template<typename T> std::set<T> get_changed_addrs(void){
        if (_state == NULL) throw uhd::runtime_error("no saved state");
        //check each register for changes
        std::set<T> addrs;
        if(_state->result != this->result){
            addrs.insert(0);
        }
        if(_state->mod != this->mod){
            addrs.insert(0);
        }
        if(_state->chn != this->chn){
            addrs.insert(0);
        }
        return addrs;
    }

private:
    ad7922_regs_t *_state;
};

#endif /* INCLUDED_AD7922_REGS_HPP */
