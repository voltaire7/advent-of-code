pub fn part1() {
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
    let out = seeds
        .into_iter()
        .map(|x| {
            let find_destination = |x, y: &Vec<(u64, u64, u64)>| {
                y.iter()
                    .find_map(|z| {
                        if x >= z.1 && x <= z.1 + z.2 {
                            Some(
                                (0..z.2)
                                    .find_map(|a| if a + z.1 == x { Some(a) } else { None })
                                    .unwrap()
                                    + z.0,
                            )
                        } else {
                            None
                        }
                    })
                    .unwrap_or(x)
            };

            let x = find_destination(x, &content[0]);
            let x = find_destination(x, &content[1]);
            let x = find_destination(x, &content[2]);
            let x = find_destination(x, &content[3]);
            let x = find_destination(x, &content[4]);
            let x = find_destination(x, &content[5]);
            let x = find_destination(x, &content[6]);
            x
        })
        .min();
    dbg!(out);
}

use std::{
    io::{stdout, Write},
    thread::sleep,
    time::Duration,
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

    let seeds = (0..seeds.len() / 2).fold(Box::new(0..0 as u64) as MyIter, |acc, x| {
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
