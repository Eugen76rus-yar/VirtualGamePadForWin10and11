 Написал небольшую программку для управлением играми, ps требует запуск от администратора т.к. используется CreateWindowInBandEx и должно работать в большинстве игр, программа на очень раннем этапе поэтому некоторые моменты ещё не обернуты
 (может не запуститься, т.к. не хватило прав и не будет никакого окна с ошибкой), нет графического редактора кнопок(в будущем сделаю).
 Основной упор при написании программы был сделан на ее универсальность и компактность. Работает с всем играми исопльзуется тот же метод наложения что и использует steam и widnows для сплывающих окон с win 8
 Для работы требуется windows 10 и новее. 
 Поддержка у GPU DX11 
 По процессору ограничений нет, на том же intel celeron n4020 при обработке четырех нажатий одновременное нагрузка на ядро не прывышала 14%
 Для запуска потребуется отключить UAC можно последовать по инструкции https://remontka.pro/uac-disable-windows-10/ если будет ошибка: "не получена ссылка" то значит UAC не выключен. 
 Советую отключить через реестр, как обходной вариант можно создать подпись своего доверенного центра и корневой сертификат, например по инструкции https://habr.com/ru/companies/tuthost/articles/152867/ и при сборке его выбрать как сертификат приложения, тогда UAC
 не требуется отключать. 
![IMG_20241205_192308](https://github.com/user-attachments/assets/3c146342-e356-4f42-a17e-04b5a47d6879)
![IMG_20241205_192703](https://github.com/user-attachments/assets/6362e271-8eb7-49a5-afc4-5a8b5db82ecd)
![IMG_20241205_192713](https://github.com/user-attachments/assets/89790c24-d2c8-485f-bfb9-79172d77517f)
