/*
 * OS Application $APP_NAME$
 */

$ACCESS_VEC$

$OWNERSHIP_VEC$

CONST(tpl_app_access, OS_APPL_CONST) $APP_NAME$_app_access = {
  {
    $PROC_ACCESS$,
    $ALARM_ACCESS$,
    $REZ_ACCESS$,
    $ST_ACCESS$,
    $CNT_ACCESS$
  },
  $PROC_OWNERSHIP$,
  $ALARM_OWNERSHIP$,
  $REZ_OWNERSHIP$,
  $ST_OWNERSHIP$,
  $CNT_OWNERSHIP$,
  $PROC_COUNT$,
  $ALARM_COUNT$,
  $REZ_COUNT$,
  $ST_COUNT$,
  $CNT_COUNT$,
  $RESTART$
};

