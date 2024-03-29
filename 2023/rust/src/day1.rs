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

use std::fs;

pub fn part1() {
    let content = fs::read_to_string("../inputs/day-1").expect("Not found");

    // Filter letters
    let content: String = content
        .chars()
        .filter(|&c| c.is_ascii_digit() || c == '\n')
        .collect();

    // Take only first and last chars
    let content: Vec<String> = content
        .split_whitespace()
        .map(|s| {
            let first = s.chars().next().unwrap().to_string();
            let last = s.chars().last().unwrap().to_string();
            first + &last
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
    let content: Vec<char> = content.chars().collect();
    let mut new: Vec<char> = Vec::new();

    let mut i = 0;
    while i < content.len() {
        let c = content[i];

        if c.is_ascii_digit() || c == '\n' {
            new.push(content[i]);
        } else {
            match c {
                'o' => {
                    if content[i + 1] == 'n' && content[i + 2] == 'e' {
                        new.push('1');
                        i += 2;
                    }
                }
                't' => {
                    if content[i + 1] == 'w' && content[i + 2] == 'o' {
                        new.push('2');
                        i += 2;
                    } else if content[i + 1] == 'h'
                        && content[i + 2] == 'r'
                        && content[i + 3] == 'e'
                        && content[i + 4] == 'e'
                    {
                        new.push('3');
                        i += 4;
                    }
                }
                'f' => {
                    if content[i + 1] == 'o' && content[i + 2] == 'u' && content[i + 3] == 'r' {
                        new.push('4');
                        i += 3;
                    } else if content[i + 1] == 'i'
                        && content[i + 2] == 'v'
                        && content[i + 3] == 'e'
                    {
                        new.push('5');
                        i += 3;
                    }
                }
                's' => {
                    if content[i + 1] == 'i' && content[i + 2] == 'x' {
                        new.push('6');
                        i += 2;
                    } else if content[i + 1] == 'e'
                        && content[i + 2] == 'v'
                        && content[i + 3] == 'e'
                        && content[i + 4] == 'n'
                    {
                        new.push('7');
                        i += 4;
                    }
                }
                'e' => {
                    if content[i + 1] == 'i'
                        && content[i + 2] == 'g'
                        && content[i + 3] == 'h'
                        && content[i + 4] == 't'
                    {
                        new.push('8');
                        i += 4;
                    }
                }
                'n' => {
                    if content[i + 1] == 'i' && content[i + 2] == 'n' && content[i + 3] == 'e' {
                        new.push('9');
                        i += 3;
                    }
                }
                _ => (),
            }
        }

        i += 1;
    }
    let content: String = new.iter().collect();

    let content: Vec<String> = content
        .split_whitespace()
        .map(|s| {
            let first = s.chars().next().unwrap().to_string();
            let last = s.chars().last().unwrap().to_string();
            first + &last
        })
        .collect();

    // Parse to number
    let content: usize = content.iter().map(|s| s.parse::<usize>().unwrap()).sum();

    dbg!(content);
}
