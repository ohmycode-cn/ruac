mod mods;
use mods::base_border::*;

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
