#ifndef DLP_SDK_GRID_CODE_HPP
#define DLP_SDK_GRID_CODE_HPP

#include <structured_light/structured_light.hpp>

/** @brief  Contains all DLP SDK classes, functions, etc. */
namespace dlp{

/** @class      GrayCode
 *  @ingroup    StructuredLight
 *  @brief      Structured Light subclass used to generate and decode Gray coded
 *              binary patterns
 */

class Grid : public dlp::StructuredLight{
public:
    class Parameters{
        public:
            DLP_NEW_PARAMETERS_ENTRY(GridSpacingRows, "GRID_PARAMETERS_SPACING_ROWS", unsigned int, 32);
            DLP_NEW_PARAMETERS_ENTRY(GridSpacingColumns, "GRID_PARAMETERS_SPACING_COLUMNS", unsigned int, 32);
            DLP_NEW_PARAMETERS_ENTRY(LineThickness, "GRID_PARAMETERS_LINE_THICKNESS", unsigned int, 1);
    };

    Grid();
    ~Grid();

    ReturnCode Setup(const dlp::Parameters &settings);
    ReturnCode GetSetup(dlp::Parameters *settings) const;
    ReturnCode GeneratePatternSequence(Pattern::Sequence *pattern_sequence);
    ReturnCode DecodeCaptureSequence(Capture::Sequence *capture_sequence,
                                     dlp::DisparityMap *disparity_map);

private:
    Parameters::GridSpacingRows    spacing_rows_;
    Parameters::GridSpacingColumns spacing_cols_;
    Parameters::LineThickness      line_thickness_;
};
}


#endif // DLP_SDK_GRID_CODE_HPP