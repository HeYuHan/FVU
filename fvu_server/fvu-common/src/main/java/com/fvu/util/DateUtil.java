package com.fvu.util;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.Locale;

import org.apache.commons.lang3.time.DateUtils;

public class DateUtil {
    private static final DateFormat df = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
    private static final DateFormat df2 = new SimpleDateFormat("yyyy.MM.dd");
    private static final DateFormat df3 = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

    public static long dateGap = 0L;

    public static String getCurrentTimeStr() {
        return df.format(now());
    }

    public static DateFormat getDf2() {
        return df2;
    }

    private static ThreadLocal<SimpleDateFormat> threadLocal = new ThreadLocal<SimpleDateFormat>() {
        @Override
        protected SimpleDateFormat initialValue() {
            return new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        }
    };

    private static ThreadLocal<SimpleDateFormat> threadLocal2 = new ThreadLocal<SimpleDateFormat>() {
        @Override
        protected SimpleDateFormat initialValue() {
            return new SimpleDateFormat("yyyy-MM-dd");
        }
    };

    public static String format(Date d) {
        return df.format(d);
    }

    public static String dateToStr(Date d) {
        return df3.format(d);
    }

    public static SimpleDateFormat getDateFormat() {
        return threadLocal.get();
    }

    public static Date parseString(String source) {
        try {
            return threadLocal2.get().parse(source);
        } catch (ParseException e) {
            try {
                return df.parse(source);
            } catch (ParseException e1) {
                try {
                    return df2.parse(source);
                } catch (ParseException e2) {
                    throw new IllegalArgumentException("不支持的日期格式");
                }
            }
        }
    }

    public static Date parseString2(String source) throws Exception {
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss", Locale.ENGLISH);
        return sdf.parse(source);
    }

    public static Date now() {
        return new Date(dateGap + System.currentTimeMillis());
    }

    //    public static Date timeTuneGap(Date time) {
    //        return new Date(dateGap + time.getTime());
    //    }
    //
    //    public static long timeTuneGap(long time) {
    //        return dateGap + time;
    //    }
    //
    public static Date dailyTime() {
        Calendar c = Calendar.getInstance();
        c.setTime(now());
        c.set(Calendar.HOUR_OF_DAY, 0);
        c.set(Calendar.MINUTE, 0);
        c.set(Calendar.SECOND, 0);
        return c.getTime();
    }

    public static Date customTime(int hour, int minute, int second){
    	Calendar c = Calendar.getInstance();
        c.setTime(now());
        c.set(Calendar.HOUR_OF_DAY, hour);
        c.set(Calendar.MINUTE, minute);
        c.set(Calendar.SECOND, second);
        return c.getTime();
    }
    //
    //
    //    public static Date specifyTime(int hour, int minute, int second) {
    //        Calendar c = Calendar.getInstance();
    //        c.setTime(now());
    //        c.set(Calendar.HOUR_OF_DAY, hour);
    //        c.set(Calendar.MINUTE, minute);
    //        c.set(Calendar.SECOND, second);
    //        return c.getTime();
    //    }

    /**
     * 取得未来离基准时间最近的，且与给定时、分、秒相同的时间。
     *
     * @param baseTime 基准时间
     * @param hour 小时
     * @param minute 分钟
     * @param second 秒
     * @return 未来离基准时间最近的，且与给定时、分、秒相同的时间
     */
    public static Date future(Date baseTime, int hour, int minute, int second) {
        Calendar cal = Calendar.getInstance();
        cal.setTime(baseTime);
        cal.set(Calendar.MILLISECOND, 0);
        cal.set(Calendar.SECOND, second);
        cal.set(Calendar.MINUTE, minute);
        cal.set(Calendar.HOUR_OF_DAY, hour);
        if (baseTime.after(cal.getTime())) {
            cal.add(Calendar.DATE, 1);
        }
        return cal.getTime();
    }

    /**
     * 取得指定日期后一天的零点时间。
     *
     * @param date
     *            指定日期
     * @return 指定日期的后一天
     */
    public static Date tomorrow(Date date) {
        Calendar cal = Calendar.getInstance();
        cal.setTime(date);
        cal.add(Calendar.DATE, 1);
        cal.set(Calendar.MILLISECOND, 0);
        cal.set(Calendar.SECOND, 0);
        cal.set(Calendar.MINUTE, 0);
        cal.set(Calendar.HOUR_OF_DAY, 0);
        return cal.getTime();
    }

    /**
     * 取得指定日期前一天的零点时间。
     *
     * @param date
     *            指定日期
     * @return 指定日期的前一天
     */
    public static Date yesterday(Date date) {
        Calendar cal = Calendar.getInstance();
        cal.setTime(date);
        cal.set(Calendar.MILLISECOND, 0);
        cal.set(Calendar.SECOND, 0);
        cal.set(Calendar.MINUTE, 0);
        cal.set(Calendar.HOUR_OF_DAY, 0);
        cal.add(Calendar.DATE, -1);
        return cal.getTime();
    }

    /**
     * 取得指定日期之后，第一个和给定“星期中的某天”一致的零点时间。
     *
     * @param date
     *            指定日期
     * @param dayOfWeek
     *            @see java.util.Calendar#DAY_OF_WEEK
     * @return 日期
     */
    public static Date nextDayOfWeek(Date date, int dayOfWeek) {
        Calendar cal = Calendar.getInstance();
        cal.setTime(date);
        int offset = dayOfWeek - cal.get(Calendar.DAY_OF_WEEK);
        if (offset <= 0) {
            offset += Calendar.DAY_OF_WEEK;
        }
        cal.add(Calendar.DAY_OF_WEEK, offset);
        cal.set(Calendar.MILLISECOND, 0);
        cal.set(Calendar.SECOND, 0);
        cal.set(Calendar.MINUTE, 0);
        cal.set(Calendar.HOUR_OF_DAY, 0);
        return cal.getTime();
    }

    /**
     * check if two date's internal is 7 days;
     *
     * @param firstDate
     * @param secondDate
     * @return
     */
    public static boolean IsNextSevenDay(Date firstDate, Date secondDate){
    	if(firstDate == null || secondDate == null){
    		return false;
    	}
    	Calendar cal1 = Calendar.getInstance();
    	cal1.setTime(firstDate);
    	Calendar cal2 = Calendar.getInstance();
    	cal2.setTime(secondDate);

    	cal1.add(Calendar.DAY_OF_YEAR, 7);

    	if(cal2.get(Calendar.YEAR) == cal1.get(Calendar.YEAR)){
    		if(cal2.get(Calendar.DAY_OF_YEAR) == cal1.get(Calendar.DAY_OF_YEAR)){
    			return true;
    		}
    	}
    	return false;
    }

    /**
     * 取得指定日期后一个月的第一天零点时间。
     *
     * @param date
     *            指定日期
     * @return 日期
     */
    public static Date nextDayOfMonth(Date date) {
        Calendar cal = Calendar.getInstance();
        cal.setTime(date);
        cal.add(Calendar.MONTH, 1);
        cal.set(Calendar.MILLISECOND, 0);
        cal.set(Calendar.SECOND, 0);
        cal.set(Calendar.MINUTE, 0);
        cal.set(Calendar.HOUR_OF_DAY, 0);
        cal.set(Calendar.DAY_OF_MONTH, 1);
        return cal.getTime();
    }

    /**
     * 取得指定日期后上个月的第一天零点时间。
     *
     * @param date
     *            指定日期
     * @return 日期
     */
    public static Date lastDayOfMonth(Date date) {
        Calendar cal = Calendar.getInstance();
        cal.setTime(date);
        cal.add(Calendar.MONTH, -1);
        cal.set(Calendar.MILLISECOND, 0);
        cal.set(Calendar.SECOND, 0);
        cal.set(Calendar.MINUTE, 0);
        cal.set(Calendar.HOUR_OF_DAY, 0);
        cal.set(Calendar.DAY_OF_MONTH, 1);
        return cal.getTime();
    }

    /**
     * 取得指定日期后上shang个月的第一天零点时间。
     *
     * @param date
     *            指定日期
     * @return 日期
     */
    public static Date FormerTwoMonth(Date date) {
        Calendar cal = Calendar.getInstance();
        cal.setTime(date);
        cal.add(Calendar.MONTH, -2);
        cal.set(Calendar.MILLISECOND, 0);
        cal.set(Calendar.SECOND, 0);
        cal.set(Calendar.MINUTE, 0);
        cal.set(Calendar.HOUR_OF_DAY, 0);
        cal.set(Calendar.DAY_OF_MONTH, 1);
        return cal.getTime();
    }

    /**
     * 取得第二天的0时的Date对象。
     *
     * @param date
     * @return
     */
    public static Date nextDayZero(Date date){
    	 Calendar cal = Calendar.getInstance();
         cal.setTime(date);
         cal.set(Calendar.MILLISECOND, 0);
         cal.set(Calendar.SECOND, 0);
         cal.set(Calendar.MINUTE, 0);
         cal.set(Calendar.HOUR_OF_DAY, 0);
         cal.set(Calendar.DAY_OF_YEAR, Calendar.DAY_OF_YEAR + 1);
         return cal.getTime();
    }
    /**
     * 取得第二天的0时的Date对象。
     *
     * @param date
     * @return
     */
    public static Date thisDayZero(Date date){
    	 Calendar cal = Calendar.getInstance();
         cal.setTime(date);
         cal.set(Calendar.MILLISECOND, 0);
         cal.set(Calendar.SECOND, 0);
         cal.set(Calendar.MINUTE, 0);
         cal.set(Calendar.HOUR_OF_DAY, 0);
         cal.set(Calendar.DAY_OF_YEAR, Calendar.DAY_OF_YEAR);
         return cal.getTime();
    }

    /**
     * 获得当前时间跟凌晨的偏移分钟数
     *
     * @param h
     * @param m
     */
    public static int getDailyGap(int h, int m) {
        return 60 * h + m;
    }

    public static void main(String[] args) {
        Calendar cal = Calendar.getInstance();
        cal.set(2013, 2, 29, 15, 37, 10);
        System.out.println(nextDayOfWeek(cal.getTime(), Calendar.TUESDAY));
    }

    public static boolean isSameDay(Date date1, Date date2) {
        return DateUtils.isSameDay(date1, date2);
    }

    public static int toUnixSeconds(Date date) {
        return date != null ? (int) (date.getTime() / 1000) : 0;
    }

    // public static void main(String[] args) {
    //
    // Calendar now =Calendar.getInstance();
    // now.setTime(new Date());
    // System.out.println(now.getTime());
    // now.set(Calendar.HOUR_OF_DAY, 0);
    // now.set(Calendar.MINUTE, 0);
    // now.set(Calendar.SECOND, 0);
    // System.out.println(now.getTime());
    //
    // // Calendar.set(Calendar.HOUR_OF_DAY, int hours)
    // // Date now =new Date();
    // // System.out.println(now);
    // // now.setHours(0);
    // // now.setMinutes(0);
    // // now.setSeconds(0);
    // // System.out.println(now);
    // }

    /**
     * 取得指定日期当月的第一天零点时间。
     *
     * @param date
     *            指定日期
     * @return 日期
     */
    public static Date firstDayOfMonth(Date date) {
        Calendar cal = Calendar.getInstance();
        cal.setTime(date);
        cal.set(Calendar.MILLISECOND, 0);
        cal.set(Calendar.SECOND, 0);
        cal.set(Calendar.MINUTE, 0);
        cal.set(Calendar.HOUR_OF_DAY, 0);
        cal.set(Calendar.DAY_OF_MONTH, 1);
        return cal.getTime();
    }

}
