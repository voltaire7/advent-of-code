pub fn part1() {
    let content = include_str!("../../inputs/day-4")
        .trim()
        .split('\n')
        .collect::<Vec<&str>>();
    let content = content
        .into_iter()
        .map(|x| {
            let x = x.split(": ").last().unwrap();
            let mut x = x.split(" | ");
            let w = x.next().unwrap();
            let a = x.next().unwrap();
            let parse = |y: &str| {
                y.split_whitespace()
                    .filter_map(|y| {
                        if y == " " {
                            None
                        } else {
                            Some(y.parse::<u32>().unwrap())
                        }
                    })
                    .collect::<Vec<u32>>()
            };
            let (w, a) = (parse(w), parse(a));
            let pow = w
                .into_iter()
                .filter(|y| a.clone().into_iter().any(|z| z == *y))
                .count() as i32
                - 1;
            if pow == -1 {
                0
            } else {
                2u32.pow(pow as u32)
            }
        })
        .sum::<u32>();
    dbg!(content);
}

pub fn part2() {
    let content = include_str!("../../inputs/day-4")
        .trim()
        .split('\n')
        .collect::<Vec<&str>>();
    let mut content = content
        .into_iter()
        .map(|x| {
            let x = x.split(": ").last().unwrap();
            let mut x = x.split(" | ");
            let w = x.next().unwrap();
            let a = x.next().unwrap();
            let parse = |y: &str| {
                y.split_whitespace()
                    .filter_map(|y| {
                        if y == " " {
                            None
                        } else {
                            Some(y.parse::<u32>().unwrap())
                        }
                    })
                    .collect::<Vec<u32>>()
            };
            let (w, a) = (parse(w), parse(a));
            (
                w.into_iter()
                    .filter(|y| a.clone().into_iter().any(|z| z == *y))
                    .count(),
                1,
            )
        })
        .collect::<Vec<(usize, usize)>>();
    (0..content.len()).for_each(|x| {
        if content[x].0 != 0 {
            (x + 1..x + 1 + content[x].0).for_each(|y| {
                content[y].1 += 1 * content[x].1;
            });
        }
    });
    dbg!(content.into_iter().map(|x| x.1).sum::<usize>());
}
