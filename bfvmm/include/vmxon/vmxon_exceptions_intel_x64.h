//
// Bareflank Hypervisor
//
// Copyright (C) 2015 Assured Information Security, Inc.
// Author: Rian Quinn        <quinnr@ainfosec.com>
// Author: Brendan Kerrigan  <kerriganb@ainfosec.com>
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

#ifndef VMXON_EXCEPTIONS_INTEL_X64_H
#define VMXON_EXCEPTIONS_INTEL_X64_H

#include <exception.h>

namespace bfn
{

// -----------------------------------------------------------------------------
// VMXON Invalid
// -----------------------------------------------------------------------------

class invalid_vmxon_error : public bfn::general_exception
{
public:
    virtual std::ostream &print(std::ostream &os) const
    { return os << "invalid vmxon"; }
};

#define invalid_vmxon() bfn::invalid_vmxon_error()

// -----------------------------------------------------------------------------
// VMXON Invalid
// -----------------------------------------------------------------------------

class vmxon_failure_error : public bfn::general_exception
{
public:
    vmxon_failure_error(const std::string &msg,
                        const std::string &func,
                        uint64_t line) :
        m_msg(msg),
        m_func(func),
        m_line(line)
    {}
    virtual ~vmxon_failure_error() {}

    virtual std::ostream &print(std::ostream &os) const
    {
        os << "vmxon failure:";
        os << std::endl << "    - reason: " << m_msg;
        os << std::endl << "    - func: " << m_func;
        os << std::endl << "    - line: " << m_line;

        return os;
    }

private:
    std::string m_msg;
    std::string m_func;
    uint64_t m_line;
};

#define vmxon_failure(a) \
    bfn::vmxon_failure_error(a,__func__,__LINE__)

// -----------------------------------------------------------------------------
// VMXON Capabilities Failure
// -----------------------------------------------------------------------------

class vmxon_capabilities_failure_error : public bfn::general_exception
{
public:
    vmxon_capabilities_failure_error(const std::string &msr_name,
                                     const std::string &field_name,
                                     uint64_t msr,
                                     uint64_t field,
                                     const std::string &func,
                                     uint64_t line) :
        m_msr_name(msr_name),
        m_field_name(field_name),
        m_msr(msr),
        m_field(field),
        m_func(func),
        m_line(line)
    {}

    virtual std::ostream &print(std::ostream &os) const
    {
        os << "vmxon capabilities not supported:";
        os << std::endl << "    - " << m_msr_name << ": " << m_msr;
        os << std::endl << "    - " << m_field_name << ": " << m_field;
        os << std::endl << "    - func: " << m_func;
        os << std::endl << "    - line: " << m_line;

        return os;
    }

private:
    std::string m_msr_name;
    std::string m_field_name;
    uint64_t m_msr;
    uint64_t m_field;
    std::string m_func;
    uint64_t m_line;
};

#define vmxon_capabilities_failure(a,b) \
    bfn::vmxon_capabilities_failure_error(#a,#b,a,b,__func__,__LINE__)

// -----------------------------------------------------------------------------
// VMXON Fixed MSR Failure
// -----------------------------------------------------------------------------

class vmxon_fixed_msr_failure_error : public bfn::general_exception
{
public:
    vmxon_fixed_msr_failure_error(const std::string &cr_name,
                                  const std::string &fixed0_name,
                                  const std::string &fixed1_name,
                                  uint64_t cr,
                                  uint64_t fixed0,
                                  uint64_t fixed1,
                                  const std::string &func,
                                  uint64_t line) :
        m_cr_name(cr_name),
        m_fixed0_name(fixed0_name),
        m_fixed1_name(fixed1_name),
        m_cr(cr),
        m_fixed0(fixed0),
        m_fixed1(fixed1),
        m_func(func),
        m_line(line)
    {}

    virtual std::ostream &print(std::ostream &os) const
    {
        os << "vmxon fixed msr bits not supported:";
        os << std::hex;
        os << std::endl << "    - " << m_cr_name << ": " << m_cr;
        os << std::endl << "    - " << m_fixed0_name << ": " << m_fixed0;
        os << std::endl << "    - " << m_fixed1_name << ": " << m_fixed1;
        os << std::endl << "    - func: " << m_func;
        os << std::endl << "    - line: " << m_line;
        os << std::dec;

        return os;
    }

private:
    const std::string &m_cr_name;
    const std::string &m_fixed0_name;
    const std::string &m_fixed1_name;
    uint64_t m_cr;
    uint64_t m_fixed0;
    uint64_t m_fixed1;
    const std::string &m_func;
    uint64_t m_line;
};

#define vmxon_fixed_msr_failure(a,b,c) \
    bfn::vmxon_fixed_msr_failure_error(#a,#b,#c,a,b,c,__func__,__LINE__)

}

#endif