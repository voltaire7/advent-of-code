// FIRST ATTEMPT
//
// fn main() {
//     let content = fs::read_to_string("../inputs/day-1").expect("Could not read file.");
//     let content: String = content
//         .chars()
//         .filter(|&c| c.is_digit(10) || c == '\n')
//         .collect();
//     let content: Vec<String> = content
//         .split_whitespace()
//         .map(|l| {
//             let len = l.len();
//             if len == 0 {
//                 panic!();
//             } else if len == 2 {
//                 l.to_owned()
//             } else if len == 1 {
//                 l.to_owned() + l
//             } else {
//                 l.chars().nth(0).unwrap().to_string() + &l.chars().nth(len - 1).unwrap().to_string()
//             }
//         })
//         .collect();
//     let content: u32 = content.into_iter().map(|n| n.parse::<u32>().unwrap()).sum();
//     dbg!(content);
// }

#![allow(dead_code)]

use std::fs;

pub fn part1() {
    let content = fs::read_to_string("../inputs/day-1").expect("Not found");

    // Filter letters
    let content: String = content
        .chars()
        .filter(|&c| c.is_digit(10) || c == '\n')
        .collect();

    // Take only first and last chars
    let content: Vec<String> = content
        .split_whitespace()
        .map(|s| {
            let first = s.chars().next().unwrap().to_string();
            let last = s.chars().last().unwrap().to_string();
            return first + &last;
        })
        .collect();

    // Parse to number
    let content: usize = content.iter().map(|s| s.parse::<usize>().unwrap()).sum();

    dbg!(content);
}

// one, two, three, four, five, six, seven, eight, nine

pub fn part2() {
    // Read entire file
    let content = fs::read_to_string("../inputs/day-1").unwrap();
    let mut chars = content.chars();

    // Get digits
    let mut new_content = String::new();
    loop {
        let c = chars.next();
        if c == None {
            break;
        }
        let c = c.unwrap();

        new_content.push(c);
    }

    dbg!(new_content);
}
