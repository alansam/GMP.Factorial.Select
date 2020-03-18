// JavaScript Document
// -------------------------------------

function createDate() {

  var _lt = '<';
  var _gt = '>';

  var lm = Date.parse(document.lastModified);
  if (!isNaN(lm) && lm != 0) {
    // normalize date
    var dlm = new Date(lm);
    var yy  = dlm.getYear();

    // Year fixups
    if (yy < 100) {
      yy += 100;
    }
    if (yy < 1000) {
      yy += 1900;
    }

    // Month fixups
    var mm = dlm.getMonth() + 1;
    if (mm < 10) {
      mm = '0' + mm;
    }

    // Day fixups
    var dd = dlm.getDate();
    if (dd < 10) {
      dd = '0' + dd;
    }

    // Date display format (ISO 8601ish): YYYY-MM-DD
    var rdate = yy + '-' + mm + '-' + dd;

    document.write('    ' + _lt + 'table width="100%" style="border-style: inherit;"' + _gt);
    document.write('      ' + _lt + 'tbody' + _gt);
    document.write('        ' + _lt + 'tr style="border-style: inherit;"' + _gt);
    document.write('          ' + _lt + 'td align="right" style="font-size: small; border-style: inherit;"' + _gt);
    document.write('            This page was last modified on ' + rdate + '.');
    document.write('          ' + _lt + '/td' + _gt);
    document.write('        ' + _lt + '/tr' + _gt);
    document.write('      ' + _lt + '/tbody' + _gt);
    document.write('    ' + _lt + '/table' + _gt);
  }

  return;
}
