#[cfg(windows)]
extern crate winapi;
use winapi::shared::minwindef::DWORD;
use winapi::um::fileapi::{CreateFileW, OPEN_EXISTING};
use winapi::um::winnt::{FILE_SHARE_READ, FILE_SHARE_WRITE, GENERIC_ALL, HANDLE};

fn main() {
    println!("Say bye! :)");
    let mut drive: HANDLE = CreateFileW(
        0,
        GENERIC_ALL,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        0 as DWORD,
        OPEN_EXISTING,
        0 as DWORD,
        0 as DWORD,
    );
}
