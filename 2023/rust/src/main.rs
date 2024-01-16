use std::env;

mod day1;
mod day2;

fn main() {
    if env::args().len() != 2 {
        println!("[ERROR] Invalid number of arguments. Please use this format: cargo run 1a");
        return;
    }
    let id = env::args().nth(1).unwrap();
    match id.as_str() {
        "1a" => day1::part1(),
        "1b" => day1::part2(),
        "2a" => day2::part1(),
        _ => println!("[ERROR] Project with id '{id}' does not exist."),
    }
}
