#include "headerfile.hpp"

#include <cstdio>
#include <map>
#include <vector>

#include "export_params.hpp"
#include "fileutils.hpp"
#include "shared.hpp"

HeaderFile header;

void HeaderFile::Write(std::ostream& file)
{
    ExportFile::Write(file);

    WriteHeaderGuard(file, params.symbol_base_name, "_H");

    if (params.for_devkitpro && params.device == "NDS")
    {
        WriteSystemInclude(file, "nds.h");
        WriteNewLine(file);
    }

    std::map<std::string, std::vector<Image*>> name_frames = GetAnimatedImages();

    bool ok_newline = false;
    if (params.transparent_given && (mode == "3" || mode == "BITMAP"))
    {
        /// TODO This needs to change new devices different datatypes.
        char buffer[7];
        sprintf(buffer, "0x%04x", Color16(params.transparent_color).ToGBAShort());
        WriteDefine(file, params.symbol_base_name, "_TRANSPARENT", buffer);
        ok_newline = true;
    }
    if (params.offset)
    {
        WriteDefine(file, params.symbol_base_name, "_PALETTE_OFFSET ", params.offset);
        ok_newline = true;
    }
    if (ok_newline) WriteNewLine(file);

    for (const auto& exportable : exportables)
        exportable->WriteExport(file);

    for (unsigned int i = 0; i < params.names.size(); i++)
    {
        const std::string& name = params.names[i];
        unsigned int frames = name_frames[name].size();
        if (frames <= 1) continue;
        const std::string& img_type = name_frames[name][0]->GetImageType();
        WriteExtern(file, img_type, name, "_frames", frames);
        // If image has a palette and splitting
        if (name_frames[name][0]->HasPalette() && params.split)
            WriteExtern(file, "const unsigned short*", name, "_palette_frames", frames);
        WriteDefine(file, name, "_FRAMES", frames);
        WriteNewLine(file);

        // Write the common #defines here.
        name_frames[name][0]->WriteCommonExport(file);
        WriteNewLine(file);
    }

    WriteEndHeaderGuard(file);
    WriteNewLine(file);
}
