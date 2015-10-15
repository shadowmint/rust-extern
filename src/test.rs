extern crate libc;

use libc::c_int;
use libc::c_char;

static mut callback:Option<extern fn(c_int)> = None;

static VALUE:&'static [u8] = b"Hello World\0";

#[no_mangle]
pub extern fn rs_str() -> *const c_char {
  return VALUE.as_ptr() as *const c_char;
}

#[no_mangle]
pub extern fn rs_trigger(val:c_int) -> c_int {
  println!("Trigger called");
  if val == 1 {
    println!("Invoking callback");
    unsafe {
      match callback {
        Some(ref cb) => {
          (*cb)(100);
        },
        _ => {
          println!("No callback bound");
        }
      }
    }
  }
  else {
    println!("Nope");
  }
  return val + 100;
}

#[no_mangle]
pub extern fn rs_register(cb: extern fn(c_int)) {
  println!("Register called");
  unsafe {
    callback = Some(cb);
  }
}
