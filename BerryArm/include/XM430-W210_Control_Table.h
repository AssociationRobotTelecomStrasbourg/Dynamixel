#ifndef XM430_W210_CONTROL_TABLE_H
#define XM430_W210_CONTROL_TABLE_H

#include <cstdint>

#include <unordered_map>
#include <string>

typedef struct
{
	uint8_t					mem_type;
	uint16_t				address;
	uint8_t					size;
	const char*			short_description;
	const char*			description;
	uint8_t					access;
	int32_t					initial;
	uint8_t					data_type;
	int32_t					range_min;
	int32_t					range_max;
	double					unit_quantum;
	const char*			unit_name;
}	dxl_registers_struct_type;

#define DXL_REG_MEM_EEPROM									0
#define DXL_REG_MEM_RAM										1
#define DXL_REG_MEM_END										2
#define DXL_REG_ACCESS_R									1
#define DXL_REG_ACCESS_W									2
#define DXL_REG_ACCESS_RW									3
#define DXL_REG_UNDEFINED_INITIAL_VALUE						0
#define DXL_REG_TYPE_UINT8									0
#define DXL_REG_TYPE_SINT8									1
#define DXL_REG_TYPE_UINT16									2
#define DXL_REG_TYPE_SINT16									3
#define DXL_REG_TYPE_UINT32									4
#define DXL_REG_TYPE_SINT32									5
#define DXL_REG_MAX_UINT32									4294967295
#define DXL_REG_MIN_SINT32									-2147483648
#define DXL_REG_MAX_SINT32									2147483647
#define DXL_REG_NO_UNIT										"NA"
#define DXL_REG_DESCRIPTION_LENGTH

typedef std::unordered_map<std::string,dxl_registers_struct_type> dxl_control_table;

void createControlTable();

#endif // XM430_W210_CONTROL_TABLE_H
