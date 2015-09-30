
#include "ProcessTools/ProcessTools.h"
#include "StructureDumpingVisitor.h"
#include "Walker.h"
#include <cstdio>
#include <iostream>

int main()
{
    std::shared_ptr<Process> process = ProcessTools::Open(_T("Wow_20444_Patched.exe"), 20444, true);
    if (!process)
        return 1;

    BSN::Protocol::Protocol const& protocolFromProcess = process->Read<BSN::Protocol::Protocol>(0x1435C04 - 0x400000);

    std::vector<std::uint8_t> byteCode = process->ReadArray<std::uint8_t>(protocolFromProcess.GetByteCode(), protocolFromProcess.GetByteCodeSize());
    std::vector<std::size_t> codeInfo = process->ReadArray<std::size_t>(protocolFromProcess.GetCodeInfo(), protocolFromProcess.GetCodeInfoSize());

    //std::vector<std::uint8_t> byteCode(327350);
    //std::vector<std::size_t> codeInfo(23120);

    //if (FILE* f = fopen("wod_alpha_bytecode.txt", "rb"))
    //{
    //    fread(byteCode.data(), 1, byteCode.size(), f);
    //    fclose(f);
    //}

    //if (FILE* f = fopen("wod_alpha_codeinfo.txt", "rb"))
    //{
    //    fread(codeInfo.data(), 1, codeInfo.size(), f);
    //    fclose(f);
    //}

    BSN::Protocol::Protocol const* protocol = new BSN::Protocol::Protocol(byteCode.data(), byteCode.size(), codeInfo.data(), codeInfo.size());

    //for (int i = 0; i < protocol->GetTypeIdCount(); ++i)
    //{
    //    if (FILE* f = fopen((std::string("out\\") + std::to_string(i) + ".txt").c_str(), "w"))
    //    {
            StructureDumpingVisitor visitor;
            StructureDumpingVisitor::Context ctx;
            ctx._protocol = protocol;
            ctx._typeId = 1697;
            BSN::Protocol::Meta::Walker::Walk(visitor, ctx);

            //fprintf(f, "%s", visitor.GetResult().c_str());
            //fclose(f);
            std::cout << visitor.GetResult();
    //    }
    //}
    return 0;
}
