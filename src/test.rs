extern crate libc;
use self::libc::c_int;

static mut callback:Option<extern fn(c_int)> = None;

#[no_mangle]
pub fn rs_trigger(val:c_int) {
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
}

#[no_mangle]
pub fn rs_register(cb: extern fn(c_int)) {
  println!("Register called");
  unsafe {
    callback = Some(cb);
  }
}
