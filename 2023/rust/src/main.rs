use std::env;

mod day1;
mod day2;
mod day3;
mod day4;

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
        "2b" => day2::part2(),
        "3a" => day3::part1(),
        "3b" => day3::part2(),
        "4a" => day4::part1(),
        "4b" => day4::part2(),
        _ => println!("[ERROR] Project with id '{id}' does not exist."),
    }
}
