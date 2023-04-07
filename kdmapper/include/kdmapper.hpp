#pragma once
#include <Windows.h>
#include <stdint.h>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

#include "portable_executable.hpp"
#include "utils.hpp"
#include "nt.hpp"
#include "intel_driver.hpp"

#define PAGE_SIZE 0x1000
#define PAGE_2MB_SIZE PAGE_SIZE * 512

namespace kdmapper
{
	typedef bool (*mapCallback)(ULONG64* param1, ULONG64* param2, ULONG64 allocationPtr, ULONG64 allocationSize, ULONG64 mdlptr);

	bool Init();
	void Dispose();

	HANDLE IntelHandle();
	//Note: if you set PassAllocationAddressAsFirstParam as true, param1 will be ignored
	uint64_t MapDriver(std::wstring driverName, ULONG64 param1 = 0, ULONG64 param2 = 0, intel_driver::ALLOCATION_TYPE allocType = intel_driver::ALLOCATION_TYPE::LargeContinuous, bool free = false, bool destroyHeader = true, bool PassAllocationAddressAsFirstParam = false, mapCallback callback = nullptr, NTSTATUS* exitCode = nullptr);
	uint64_t MapDriver(BYTE* data, ULONG64 param1 = 0, ULONG64 param2 = 0, intel_driver::ALLOCATION_TYPE allocType = intel_driver::ALLOCATION_TYPE::LargeContinuous, bool free = false, bool destroyHeader = true, bool PassAllocationAddressAsFirstParam = false, mapCallback callback = nullptr, NTSTATUS* exitCode = nullptr);
	
	uint64_t AllocMdlMemory(uint64_t size, uint64_t* mdlPtr);
}