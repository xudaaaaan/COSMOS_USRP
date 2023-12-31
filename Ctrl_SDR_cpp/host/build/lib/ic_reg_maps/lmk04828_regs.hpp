/***********************************************************************
 * This file was generated by /root/uhd/host/lib/ic_reg_maps/gen_lmk04828_regs.py on Thu Jun  2 22:24:08 2022
 **********************************************************************/

#ifndef INCLUDED_LMK04828_REGS_HPP
#define INCLUDED_LMK04828_REGS_HPP

#include <uhd/config.hpp>
#include <uhd/exception.hpp>
#include <set>
#include <stdint.h>

class lmk04828_regs_t{
public:
    uint16_t address0;
    uint8_t Reset;
    uint8_t Reserved_0_0;
    enum SPI_3wire_t{
        SPI_3WIRE_ENABLE = 0,
        SPI_3WIRE_DISABLE = 1
    };
    SPI_3wire_t SPI_3wire;
    uint8_t Reserved_0_1;
    uint16_t address1;
    uint8_t Reserved_1_0;
    uint16_t address2;
    uint8_t Reserved_2_0;
    enum Powerdown_t{
        POWERDOWN_NORMAL = 0,
        POWERDOWN_POWERDOWN = 1
    };
    Powerdown_t Powerdown;
    uint16_t address3;
    uint8_t ID_Device_Type;
    uint16_t address4;
    uint8_t ID_Prod_MSB;
    uint16_t address5;
    uint8_t ID_Prod_LSB;
    uint16_t address6;
    enum ID_MaskRev_t{
        ID_MASKREV_LMK04821 = 36,
        ID_MASKREV_LMK04826 = 37,
        ID_MASKREV_LMK04828 = 32
    };
    ID_MaskRev_t ID_MaskRev;
    uint16_t address12;
    uint8_t ID_Vendor_MSB;
    uint16_t address13;
    uint8_t ID_Vendor_LSB;

    lmk04828_regs_t(void){
        _state = NULL;
        address0 = 0;
        Reset = 0;
        Reserved_0_0 = 0;
        SPI_3wire = SPI_3WIRE_ENABLE;
        Reserved_0_1 = 0;
        address1 = 1;
        Reserved_1_0 = 0;
        address2 = 2;
        Reserved_2_0 = 0;
        Powerdown = POWERDOWN_NORMAL;
        address3 = 3;
        ID_Device_Type = 6;
        address4 = 4;
        ID_Prod_MSB = 208;
        address5 = 5;
        ID_Prod_LSB = 91;
        address6 = 6;
        ID_MaskRev = ID_MASKREV_LMK04828;
        address12 = 12;
        ID_Vendor_MSB = 81;
        address13 = 13;
        ID_Vendor_LSB = 4;
    }

    ~lmk04828_regs_t(void){
        delete _state;
    }

    
    
    
    
    uint32_t get_reg(int addr){
        uint32_t reg = 0;
        switch(addr){
        case 0:
            reg |= (uint32_t(address0) & 0x1fff) << 8;
            reg |= (uint32_t(Reset) & 0x1) << 7;
            reg |= (uint32_t(Reserved_0_0) & 0x3) << 5;
            reg |= (uint32_t(SPI_3wire) & 0x1) << 4;
            reg |= (uint32_t(Reserved_0_1) & 0xf) << 0;
            break;
        case 1:
            reg |= (uint32_t(address1) & 0x1fff) << 8;
            reg |= (uint32_t(Reserved_1_0) & 0xff) << 0;
            break;
        case 2:
            reg |= (uint32_t(address2) & 0x1fff) << 8;
            reg |= (uint32_t(Reserved_2_0) & 0x7f) << 1;
            reg |= (uint32_t(Powerdown) & 0x1) << 0;
            break;
        case 3:
            reg |= (uint32_t(address3) & 0x1fff) << 8;
            reg |= (uint32_t(ID_Device_Type) & 0xff) << 0;
            break;
        case 4:
            reg |= (uint32_t(address4) & 0x1fff) << 8;
            reg |= (uint32_t(ID_Prod_MSB) & 0xff) << 0;
            break;
        case 5:
            reg |= (uint32_t(address5) & 0x1fff) << 8;
            reg |= (uint32_t(ID_Prod_LSB) & 0xff) << 0;
            break;
        case 6:
            reg |= (uint32_t(address6) & 0x1fff) << 8;
            reg |= (uint32_t(ID_MaskRev) & 0xff) << 0;
            break;
        case 12:
            reg |= (uint32_t(address12) & 0x1fff) << 8;
            reg |= (uint32_t(ID_Vendor_MSB) & 0xff) << 0;
            break;
        case 13:
            reg |= (uint32_t(address13) & 0x1fff) << 8;
            reg |= (uint32_t(ID_Vendor_LSB) & 0xff) << 0;
            break;
        }
        return reg;
    }

    void save_state(void){
        if (_state == NULL) _state = new lmk04828_regs_t();
        _state->address0 = this->address0;
        _state->Reset = this->Reset;
        _state->Reserved_0_0 = this->Reserved_0_0;
        _state->SPI_3wire = this->SPI_3wire;
        _state->Reserved_0_1 = this->Reserved_0_1;
        _state->address1 = this->address1;
        _state->Reserved_1_0 = this->Reserved_1_0;
        _state->address2 = this->address2;
        _state->Reserved_2_0 = this->Reserved_2_0;
        _state->Powerdown = this->Powerdown;
        _state->address3 = this->address3;
        _state->ID_Device_Type = this->ID_Device_Type;
        _state->address4 = this->address4;
        _state->ID_Prod_MSB = this->ID_Prod_MSB;
        _state->address5 = this->address5;
        _state->ID_Prod_LSB = this->ID_Prod_LSB;
        _state->address6 = this->address6;
        _state->ID_MaskRev = this->ID_MaskRev;
        _state->address12 = this->address12;
        _state->ID_Vendor_MSB = this->ID_Vendor_MSB;
        _state->address13 = this->address13;
        _state->ID_Vendor_LSB = this->ID_Vendor_LSB;
    }

    template<typename T> std::set<T> get_changed_addrs(void){
        if (_state == NULL) throw uhd::runtime_error("no saved state");
        //check each register for changes
        std::set<T> addrs;
        if(_state->address0 != this->address0){
            addrs.insert(0);
        }
        if(_state->Reset != this->Reset){
            addrs.insert(0);
        }
        if(_state->Reserved_0_0 != this->Reserved_0_0){
            addrs.insert(0);
        }
        if(_state->SPI_3wire != this->SPI_3wire){
            addrs.insert(0);
        }
        if(_state->Reserved_0_1 != this->Reserved_0_1){
            addrs.insert(0);
        }
        if(_state->address1 != this->address1){
            addrs.insert(1);
        }
        if(_state->Reserved_1_0 != this->Reserved_1_0){
            addrs.insert(1);
        }
        if(_state->address2 != this->address2){
            addrs.insert(2);
        }
        if(_state->Reserved_2_0 != this->Reserved_2_0){
            addrs.insert(2);
        }
        if(_state->Powerdown != this->Powerdown){
            addrs.insert(2);
        }
        if(_state->address3 != this->address3){
            addrs.insert(3);
        }
        if(_state->ID_Device_Type != this->ID_Device_Type){
            addrs.insert(3);
        }
        if(_state->address4 != this->address4){
            addrs.insert(4);
        }
        if(_state->ID_Prod_MSB != this->ID_Prod_MSB){
            addrs.insert(4);
        }
        if(_state->address5 != this->address5){
            addrs.insert(5);
        }
        if(_state->ID_Prod_LSB != this->ID_Prod_LSB){
            addrs.insert(5);
        }
        if(_state->address6 != this->address6){
            addrs.insert(6);
        }
        if(_state->ID_MaskRev != this->ID_MaskRev){
            addrs.insert(6);
        }
        if(_state->address12 != this->address12){
            addrs.insert(12);
        }
        if(_state->ID_Vendor_MSB != this->ID_Vendor_MSB){
            addrs.insert(12);
        }
        if(_state->address13 != this->address13){
            addrs.insert(13);
        }
        if(_state->ID_Vendor_LSB != this->ID_Vendor_LSB){
            addrs.insert(13);
        }
        return addrs;
    }

private:
    lmk04828_regs_t *_state;
};

#endif /* INCLUDED_LMK04828_REGS_HPP */
