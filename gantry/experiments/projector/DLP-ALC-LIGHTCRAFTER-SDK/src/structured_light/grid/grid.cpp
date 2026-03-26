#include <structured_light/grid/grid.hpp>
#include <common/image/image.hpp>

namespace dlp {

/** @brief Constructs object */
Grid::Grid(){
    this->debug_.SetName("STRUCTURED_LIGHT_GRAY_CODE(" + dlp::Number::ToString(this)+ "): ");
    this->debug_.Msg("Constructing object...");
    this->is_setup_ = false;
    this->disparity_map_.Clear();
    this->pattern_color_.Set(dlp::Pattern::Color::WHITE);
    this->debug_.Msg("Object constructed");
}

/** @brief Destroys object and deallocates memory */
Grid::~Grid(){
    this->debug_.Msg("Deconstructing object...");
    this->disparity_map_.Clear();
    this->debug_.Msg("Object deconstructed");
}

ReturnCode Grid::Setup(const dlp::Parameters &settings){
    ReturnCode ret;

    // Pull parameters (falls back to defaults if missing)
    settings.Get(&spacing_rows_);
    settings.Get(&spacing_cols_);
    settings.Get(&line_thickness_);

    // These come from StructuredLight base - required
    if (settings.Get(&pattern_color_).hasErrors())
        return ret.AddError(STRUCTURED_LIGHT_SETTINGS_PATTERN_COLOR_MISSING);

    if(!this->projector_set_){
        if(settings.Get(&this->pattern_rows_).hasErrors())
            return ret.AddError(STRUCTURED_LIGHT_SETTINGS_PATTERN_ROWS_MISSING);

       if((settings.Get(&this->pattern_columns_).hasErrors()))
            return ret.AddError(STRUCTURED_LIGHT_SETTINGS_PATTERN_COLUMNS_MISSING);
    }
    
    this->sequence_count_total_ = 1; // single pattern
    return ret;
}

ReturnCode Grid::GeneratePatternSequence(Pattern::Sequence *pattern_sequence){
    ReturnCode ret;
    if (!pattern_sequence)
        return ret.AddError(STRUCTURED_LIGHT_PATTERN_SEQUENCE_NULL);

    unsigned int rows = pattern_rows_.Get();
    unsigned int cols = pattern_columns_.Get();
    unsigned int spacing_r = spacing_rows_.Get();
    unsigned int spacing_c = spacing_cols_.Get();
    unsigned int thickness = line_thickness_.Get();

    // Create an image for the grid
    dlp::Image grid_image;
    grid_image.Create(cols, rows, dlp::Image::Format::RGB_UCHAR);
    // Set color patterns
    dlp::PixelRGB black;
    black.r = 0;
    black.g = 0;
    black.b = 0;

    dlp::PixelRGB white;
    white.r = 255;
    white.g = 255;
    white.b = 255;
    // Fill background black
    grid_image.FillImage(black);

    // Draw horizontal lines
    for (unsigned int r = 0; r < rows; r++) {
        if (r % spacing_r < thickness) {
            for (unsigned int c = 0; c < cols; c++) {
                grid_image.SetPixel(c, r, white);
            }
        }
    }

    // Draw vertical lines
    for (unsigned int c = 0; c < cols; c++) {
        if (c % spacing_c < thickness) {
            for (unsigned int r = 0; r < rows; r++) {
                grid_image.SetPixel(c, r, white);
            }
        }
    }

    // Package into a pattern
    dlp::Pattern grid_pattern;
    grid_pattern.color       = pattern_color_.Get();
    grid_pattern.image_data  = grid_image;
    grid_pattern.data_type   = dlp::Pattern::DataType::IMAGE_DATA;

    pattern_sequence->Clear();
    pattern_sequence->Add(grid_pattern);

    return ret;
}

ReturnCode Grid::DecodeCaptureSequence(Capture::Sequence *capture_sequence,
                                        dlp::DisparityMap *disparity_map) {
    ReturnCode ret;
    // Grid doesn't decode - it's a display pattern only
    // Leave empty or return a not-implemented error
    return ret;
}

ReturnCode Grid::GetSetup(dlp::Parameters *settings) const {
    ReturnCode ret;
    if (!settings) return ret.AddError(STRUCTURED_LIGHT_NULL_POINTER_ARGUMENT);
    settings->Set(spacing_rows_);
    settings->Set(spacing_cols_);
    settings->Set(line_thickness_);
    settings->Set(pattern_rows_);
    settings->Set(pattern_columns_);
    settings->Set(pattern_color_);
    return ret;
}
}