// JavaScript No-ops
// -------------------------------------

function nop() {
  document.write("");
  return;
}

function noop() {
  nop();
  return;
}

function xyzzy() {
  document.write("Nothing happens");
  return;
}

function plover() {
  var _lt  = '\u003c';
  var _gt  = '\u003e';
  var _lsq = '\u2018';
  var _rsq = '\u2019';
  var _ldq = '\u201c';
  var _rdq = '\u201d';
  var pq = ''
    + _lsq
    + 'An emerald '
    + _lt
    +  'span class="script" style="font-weight: bolder; font-size: 120%;"'
    + _gt
    + _ldq
    + 'the size of a plover'
    + _rsq
    +'s egg!'
    + _rdq
    + _lt
    + '/span'
    + _gt
    + _rsq
    ;
  document.write(pq);
  return;
}

//function plugh() {
//
//  var _lt  = '\u003c';
//  var _gt  = '\u003e';
//  var _lsq = '\u2018';
//  var _rsq = '\u2019';
//  var _ldq = '\u201c';
//  var _rdq = '\u201d';
//  document.write(''
//    + _lsq
//    + 'A hollow voice says: '
//    + _lt
//    +  'span class="script" style="font-weight: bolder; font-size: 120%;"'
//    + _gt
//    + _ldq
//    + 'Plugh!'
//    + _rdq
//    + _lt
//    + '/span'
//    + _gt
//    + _rsq
//    );
//
//  return;
//}
