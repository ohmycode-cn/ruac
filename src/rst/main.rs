fn col(line_: i32) -> String {
    let left: &str = "║";
    let right: &str = "║";
    return format!("{}{}{}", left, " ".repeat(line_ as usize), right);
}

fn row(line_: i32) -> String {
    return format!("{}", "═".repeat(line_ as usize));
}

fn cnr_left_up(char_: char) -> String {
    return format!("{}", char_);
}

fn cnr_right_up(char_: char) -> String {
    return format!("{}", char_);
}

fn cnr_left_dn(char_: char) -> String {
    return format!("{}", char_);
}

fn cnr_right_dn(char_: char) -> String {
    return format!("{}", char_);
}

fn draw(
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

fn main() {
    println!("[Welcome To Use Rust RuacDB Model]");
    draw(
        cnr_left_up('╔'),
        cnr_right_up('╗'),
        cnr_left_dn('╚'),
        cnr_right_dn('╝'),
        row(84),
        col(84),
        84,
    );
}
