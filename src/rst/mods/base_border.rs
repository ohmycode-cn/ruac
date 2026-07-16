/// Generates a vertical column string with left and right border characters.
///
/// The column is constructed by concatenating a left border character ("║"),
/// a sequence of spaces of length `line_`, and a right border character ("║").
///
/// # Arguments
///
/// * `line_` - The number of spaces between the left and right borders.
///
/// # Returns
///
/// A `String` representing the formatted column.
pub fn col(line_: i32) -> String {
    let left: &str = "║";
    let right: &str = "║";
    return format!("{}{}{}", left, " ".repeat(line_ as usize), right);
}

/// Generates a horizontal row string composed of repeated border characters.
///
/// The row is formed by repeating the character "═" `line_` times.
///
/// # Arguments
///
/// * `line_` - The number of times to repeat the border character.
///
/// # Returns
///
/// A `String` representing the formatted row.
pub fn row(line_: i32) -> String {
    return format!("{}", "═".repeat(line_ as usize));
}

/// Converts the given character to a string, intended for the top-left corner.
///
/// # Arguments
///
/// * `char_` - The character to be converted (e.g., '╔').
///
/// # Returns
///
/// A `String` containing the character.
pub fn cnr_left_up(char_: char) -> String {
    return format!("{}", char_);
}

/// Converts the given character to a string, intended for the top-right corner.
///
/// # Arguments
///
/// * `char_` - The character to be converted (e.g., '╗').
///
/// # Returns
///
/// A `String` containing the character.
pub fn cnr_right_up(char_: char) -> String {
    return format!("{}", char_);
}

/// Converts the given character to a string, intended for the bottom-left corner.
///
/// # Arguments
///
/// * `char_` - The character to be converted (e.g., '╚').
///
/// # Returns
///
/// A `String` containing the character.
pub fn cnr_left_dn(char_: char) -> String {
    return format!("{}", char_);
}

/// Converts the given character to a string, intended for the bottom-right corner.
///
/// # Arguments
///
/// * `char_` - The character to be converted (e.g., '╝').
///
/// # Returns
///
/// A `String` containing the character.
pub fn cnr_right_dn(char_: char) -> String {
    return format!("{}", char_);
}

/// Draws a rectangular border using the provided corner characters, row, and column strings.
///
/// The border consists of a top row, a bottom row, and a series of vertical columns.
/// The number of columns printed is `rows_ / 6` (integer division).
///
/// # Arguments
///
/// * `cnr_left_up_` - String for the top-left corner (e.g., "╔").
/// * `cnr_right_up_` - String for the top-right corner (e.g., "╗").
/// * `cnr_left_dn_` - String for the bottom-left corner (e.g., "╚").
/// * `cnr_right_dn_` - String for the bottom-right corner (e.g., "╝").
/// * `row_` - String for the horizontal row (e.g., a sequence of "═").
/// * `col_` - String for each vertical column (e.g., a left border, spaces, right border).
/// * `rows_` - A parameter that determines the number of columns (actual columns = rows_ / 6).
pub fn draw(
    cnr_left_up_: String,
    cnr_right_up_: String,
    cnr_left_dn_: String,
    cnr_right_dn_: String,
    row_: String,
    col_: String,
    rows_: i32,
) {
    print!("{}", cnr_left_up_);
    print!("{}", row_);
    println!("{}", cnr_right_up_);

    for _ in 0..(rows_ / 6) as usize {
        println!("{}", col_);
    }

    print!("{}", cnr_left_dn_);
    print!("{}", row_);
    println!("{}", cnr_right_dn_);
}
