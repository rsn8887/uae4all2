@set /p title="Insert bubble name (Example: Superfrog): "
@set /p conf="Insert config name (Example: ux0:/data/uae4all/conf/superfrog.conf): "
@set /p id="Insert bubble title ID (9 characters [NOTE: Only UPPERCASE letters or numbers]): "
@echo|set /p="%conf%"> "assets/args.txt"
vita-mksfoex -s TITLE_ID=%id% "%title%" param.sfo
vita-pack-vpk -s param.sfo -b eboot.bin "%title%.vpk" -a assets/icon0.png=sce_sys/icon0.png -a assets/bg.png=sce_sys/livearea/contents/bg.png -a assets/startup.png=sce_sys/livearea/contents/startup.png -a assets/template.xml=sce_sys/livearea/contents/template.xml -a assets/args.txt=args.txt
