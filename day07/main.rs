use std::borrow::Borrow;
use std::fs;

fn main() {
    let filename = "data.txt";
    let contents = fs::read_to_string(filename)
        .expect("Something went wrong reading the file");
    let numbers: Vec<i32> = contents.split(',').map(|s| s.parse().unwrap()).collect();
    let start_n = (numbers.iter().sum::<i32>() as f32 / numbers.len() as f32).round() as i32;
    let mut new_n = start_n;
    let result_start = numbers.iter().map(|x| (x - new_n).abs()).sum::<i32>();
    let mut result_old = result_start;
    loop {
        new_n = new_n - 1;
        let result_new = numbers.iter().map(|x| (x - new_n).abs()).sum::<i32>();
        if result_new > result_old {
            new_n = new_n + 1;
            break;
        }
        result_old = result_new;
        println!("result {} {}", new_n, result_old);
    }
    loop {
        new_n = new_n + 1;
        let result_new = numbers.iter().map(|x| (x - new_n).abs()).sum::<i32>();
        if result_new > result_old {
            new_n = new_n - 1;
            break;
        }
        result_old = result_new;
        println!("result {} {}", new_n, result_old);
    }
    println!("result part 1 {} {}", new_n, result_old);


    let mut new_n = start_n;
    let result_start = numbers.iter().map(|x| (0.5 * ((x - new_n).abs() * ((x - new_n).abs() + 1)) as f32) as i32).sum::<i32>();
    let results2: Vec<i32> = numbers.iter().map(|x| (0.5 * ((x - new_n).abs() * ((x - new_n).abs() + 1)) as f32) as i32).collect();
    println!("{:?}", results2);
    println!("{:?}", numbers);
    let mut result_old = result_start;
    loop {
        new_n = new_n - 1;
        let result_new = numbers.iter().map(|x| (0.5 * ((x - new_n).abs() * ((x - new_n).abs() + 1)) as f32) as i32).sum::<i32>();
        if result_new > result_old {
            new_n = new_n + 1;
            break;
        }
        result_old = result_new;
        println!("result {} {}", new_n, result_old);
    }
    loop {
        new_n = new_n + 1;
        let result_new = numbers.iter().map(|x| (0.5 * ((x - new_n).abs() * ((x - new_n).abs() + 1)) as f32) as i32).sum::<i32>();
        if result_new > result_old {
            new_n = new_n - 1;
            break;
        }
        result_old = result_new;
        println!("result {} {}", new_n, result_old);
    }
    println!("result part 2 {} {}", new_n, result_old);
}