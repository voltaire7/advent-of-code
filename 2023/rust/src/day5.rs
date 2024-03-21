pub fn part1() {
    let content = include_str!("../../inputs/day-5").trim().split("\n\n");
    let seeds = content
        .clone()
        .next()
        .unwrap()
        .split_whitespace()
        .skip(1)
        .map(|x| x.parse::<u64>().unwrap());
    let maps = content.into_iter().skip(1).map(|x| {
        let mut x = x
            .split(|y| y == '\n' || y == ' ')
            .skip(2)
            .map(|y| y.parse::<u64>().unwrap());
        (0..x.clone().count() / 3)
            .map(move |_| (x.next().unwrap(), x.next().unwrap(), x.next().unwrap()))
    });
    let result = seeds
        .map(|x| {
            maps.clone().fold(x, |prev, next| {
                next.clone()
                    .find(|item| prev >= item.1 && prev <= item.1 + item.2)
                    .map(|item| item.0 + item.2 - prev.abs_diff(item.1 + item.2))
                    .unwrap_or(prev)
            })
        })
        .min()
        .unwrap();
    dbg!(result);
}

use std::{
    io::{stdout, Write},
    thread::sleep,
    time::Duration,
    u64,
};
type MyIter = Box<dyn Iterator<Item = u64>>;

pub fn part2() {
    let content = include_str!("../../inputs/day-5")
        .trim()
        .split("\n\n")
        .collect::<Vec<&str>>();

    let seeds = content
        .first()
        .unwrap()
        .split_whitespace()
        .skip(1)
        .map(|x| x.parse::<u64>().unwrap())
        .collect::<Vec<u64>>();

    let seeds = (0..seeds.len() / 2).fold(Box::new(0..0_u64) as MyIter, |acc, x| {
        Box::new(acc.chain(Box::new(seeds[x * 2]..seeds[x * 2 + 1]) as MyIter)) as MyIter
    });

    let content = content
        .iter()
        .skip(1)
        .map(|x| {
            let mut x = x
                .split(|y| y == '\n' || y == ' ')
                .skip(2)
                .map(|y| y.parse::<u64>().unwrap());
            (0..x.clone().count() / 3)
                .map(|_| (x.next().unwrap(), x.next().unwrap(), x.next().unwrap()))
                .collect::<Vec<(u64, u64, u64)>>()
        })
        .collect::<Vec<Vec<(u64, u64, u64)>>>();

    let constant_search = |target: u64, items: &Vec<(u64, u64, u64)>| -> u64 {
        for item in items {
            if target >= item.1 && target <= item.1 + item.2 {
                let diff = target.abs_diff(item.1 + item.2);
                return item.0 + item.2 - diff;
            }
        }
        target
    };

    let mut seed_count: f64 = 0.0;
    let mut stdout = stdout();

    let out = seeds
        .map(|x| {
            print!(
                "\rProcessing: {} / 269431899, {:.2} %",
                seed_count as u64,
                seed_count / 269431899.0 * 100.0
            );
            // print!("\rProcessing {:.2} %", seed_count / 269431899.0 * 100.0);
            stdout.flush().unwrap();
            sleep(Duration::from_millis(20));
            let x = constant_search(x, &content[0]);
            let x = constant_search(x, &content[1]);
            let x = constant_search(x, &content[2]);
            let x = constant_search(x, &content[3]);
            let x = constant_search(x, &content[4]);
            let x = constant_search(x, &content[5]);
            let x = constant_search(x, &content[6]);
            seed_count += 1.0;
            x
        })
        .min();
    dbg!(out);
}
