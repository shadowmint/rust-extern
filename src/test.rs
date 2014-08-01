extern crate libc;
use self::libc::c_int;

#[no_mangle]
pub fn doit(val:c_int) -> c_int {
  return val as i32 + 10;
}
