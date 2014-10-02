
similarproducts.gameHour  =
{
	$: spsupport.p.$,
	appDomain: spsupport.p.sfDomain,
	hostDomain: null,
    whitelist: /^(adventuregamers\.com|bolumsonucanavari\.com|carls-sims-3-guide\.com|cheapshark\.com|corsair\.com|donanimhaber\.com|dragonage\.com|epicbundle\.com|g2a\.com|g2play\.net|gamebase\.com\.tw|gameboomers\.com|gamepressure\.com|gamesrocket\.com|gamesrocket\.de|gpro\.net|gratisjuegos\.org|hamster-joueur\.com|hwupgrade\.it|indiegamestand\.com|indieroyale\.com|instant-gaming\.com|intercambiosvirtuales\.org|macgamestore\.com|matrixgames\.com|nuuvem\.com\.br|paradoxplaza\.com|parkoz\.com|pcwelt\.de|playblink\.com|playfire\.com|playwares\.com|ps3news\.com|riseofflight\.com|steamgamesales\.com|taringa\.net|techbargains\.com|teksyndicate\.com|titanfall\.com|virtualr\.net|wargamer\.com|worldofspectrum\.org|origin\.com|gamersgate\.com|gog\.com|humblebundle\.com|getgamesgo\.com|gamesplanet\.com|impulsedriven\.com|gamestop\.com|greenmangaming\.com|gamefly\.com|ubi\.com|minecraft\.net|xbox\.com|nintendo\.com|onlive\.com|bundlestars\.com|ign\.com|twitch\.tv|gamespot\.com|polygon\.com|kotaku\.com|destructoid\.com|isthereanydeal\.com|g4tv\.com|curse\.com|gamepedia\.com|mmo-champion\.com|incgamers\.com|eurogamer\.net|usgamer\.net|rockpapershotgun\.com|gamerevolution\.com|mobygames\.com|videogamer\.com|giantbomb\.com|joystiq\.com|gamefaqs\.com|battlefield\.com|ea\.com|rockstargames\.com|majorleaguegaming\.com|nexusmods\.com|178\.com|pcgamer\.com|neogaf\.com|steamgifts\.com|steamcommunity\.com|easports\.com|arstechnica\.com|xfire\.com|edge-online\.com|egmnow\.com|cheapassgamer\.com|1up\.com|gamesradar\.com|escapistmagazine\.com|neoseeker\.com|gamefront\.com|cheatcc\.com|gamespy\.com|supercheats\.com|metacritic\.com|diablofans\.com|diabloprogress\.com|wowprogress\.com|jeuxvideo\.com|duowan\.com|thesims\.com|thesims3\.com|3djuegos\.com|gamersky\.com|serebii\.net|emuparadise\.me|gratisjuegos\.org|inven\.co\.kr|tgbus\.com|4399\.com|ali213\.net|3dmgame\.com|gamebreaker\.tv|gamerswithjobs\.com|whosgamingnow\.com|kitguru\.net|pcgamingwiki\.com|computerandvideogames\.com|n4g\.com|officialplaystationmagazine\.co\.uk|totalxbox\.com|techtudo\.com\.br|commentcamarche\.net|gamewise\.co|recode\.net|teamliquid\.net|mcvuk\.com|enjin\.com|gamespress\.com|gamesindustry\.biz|vgchartz\.com|gamrreview\.com|callofduty\.com|needforspeed\.com|gtaforums\.com|megagames\.com|gamezone\.com|bioware\.com|gamerankings\.com|cheathappens\.com|shacknews\.com|gamasutra\.com|vg247\.com|gameinformer\.com|elderscrollsonline\.com|twcenter\.net|bluesnews\.com|gametrailers\.com|techspot\.com|zam\.com|rpgwatch\.com|obsidian\.net|pluggedin\.com|gaygamer\.net|actiontrip\.com|allgame\.com|evilavatar\.com|dualshockers\.com|strategyinformer\.com|avclub\.com|gamepur\.com|gamewinners\.com|playstationtrophies\.org|playstation\.com|wikia\.com|gameranx\.com|gamingbolt\.com|hardforum\.com|bjorn3d\.com|razerzone\.com|pcgameshardware\.com|battle\.net|tech-forums\.net|neowin\.net|alienwarearena\.com|guru3d\.com|dsogaming\.com|pcper\.com|geforce\.com|hardcoreware\.net|amd\.com|tegrazone\.com|msi\.com|extremetech\.com|gamersnexus\.net|empireonline\.com|bungie\.net|allgamesbeta\.com|vakarm\.net|coolrom\.co\.uk|coolrom\.com|theoldcomputer\.com|nexon\.com|epforums\.org|meristation\.com|skydaz\.com|17173\.com|playground\.ru|joindota\.com|dota2\.com|playdota\.com|axeso5\.com|gamer\.com\.tw|psu\.com|retrogamer\.com|hltv\.org|gamebanana\.com|multiplayer\.it|siliconera\.com|eventhubs\.com|411mania\.com|dorkly\.com|gamer\.nl|thesixthaxis\.com|pushsquare\.com|gamevicio\.com|kotaku\.com\.au|majornelson\.com|indiegames\.com|commandandconquer\.com|trionworlds\.com|valvesoftware\.com|quartertothree\.com)$/i,
    pageWhiteList: /.+\.craigslist\.org\/(.+?\/)?vgm\/|battlefield\.play4free\.com|store\.steampowered\.com|digital\.gamefly\.com|store\.sonyentertainmentnetwork\.com|jeux-video\.fnac\.com|games\.yahoo\.com|jogos\.uol\.com\.br|news\.yahoo\.com|headlines\.yahoo\.co\.jp|compactiongames\.about\.com|answers\.yahoo\.com|blog\.games\.com|gaming\.stackexchange\.com/i,
	serverLayerFrame: null,
	minimizedMode: false,
	initialMinimizingTimer: null,

	serverData:
	{
		items: [],
		sessionId: null
	},

	view:
	{
		self: null
	},

	initialize: function()
	{
		this.hostDomain = this.utils.extractDomainName(location.host);

		if (this.whitelist.test(this.hostDomain) || this.pageWhiteList.test(location.href))
		{
			this.startFlow();
		}
	},

	startFlow: function()
	{
		var sb = similarproducts.b;
		var domainName = this.utils.extractDomainName(document.location.host);
		var serverLayerFrameParams =
		{
			documentTitle: document.title + ' | ' + location.hash + ' | ' + location.search,
			dlSource: sb.dlsource,
			userId: sb.userid,
			ctid: sb.CD_CTID,
			version: sb.appVersion,
			pageUrl: location.href,
			sourceDomain: this.appDomain,
			merchantName: domainName,
            browser : spsupport.api.dtBr(),
            clientCountry: sb.userData.uc
		};

		sb.inj(document, this.appDomain+'gh/css/main.css?v='+sb.appVersion);

		this.$(window).bind("message", this.utils.serverMessagesRouter.bind(this));

		this.serverLayerFrame = this.$('<iframe />',
		{
			style: 'position:absolute; width:0; height:0; left:-100px; top:-100px;',
			src: this.appDomain + 'gh/server_layer.html?' + this.utils.compileQueryString(serverLayerFrameParams) + similarproducts.utilities.abTestUtil.getDataString()
		})[0];

		document.body.appendChild(this.serverLayerFrame);
	},


	processServerData: function(data) // This function is called by the "utils.serverMessagesRouter" func via the "fn" param send by the server layer
	{
		var item;

		this.serverData = data;
		item = this.serverData.item;

		similarproducts.Template.initialize(data.template);

		if (item)
		{
			if (!item.you_save_text || item.you_save_text == '0%')
			{
				item.you_save_text = null;
				item.platform = item.platformName.split(' ')[0];
			}
		}

        similarproducts.utilities.newUnit('gameHour');

		this.render();
		this.defineViewElements();
		this.positionToView();
		this.renderInfo();
		this.postRender();
		this.activate();
	},

	render: function()
	{
		this.$('body').append(similarproducts.Template.render('gameHourMain',
		{
			partnerName: similarproducts.b.qsObj.partnername || similarproducts.b.psuSupportedByText,
			item: this.serverData.item
		}));
	},

	defineViewElements: function()
	{
		this.view.self = this.$('#similarproducts_gamehour'),
		this.view.unitHeader = this.$('._unit_header', this.view.self),
		this.view.closeButton = this.$('._close', this.view.self),
		this.view.minimizeButton = this.$('._minimize', this.view.self),
		this.view.restoreButton = this.$('._restore', this.view.self),
		this.view.infoButton = this.$('._show_info', this.view.self),
		this.view.disableButton = this.$('._disable', this.view.self)
	},

	postRender: function()
	{
		if (this.$.browser.msie && parseInt(spsupport.p.$.browser.version) < 10)
		{
			this.view.self.addClass('legacy_browser');
		}
	},

	activate: function()
	{
		this.view.self.one('mouseover', this.cancelInitialMinimizing.bind(this));
		this.view.infoButton.click(this.showInfo.bind(this));
		this.view.closeButton.click(this.closeUnit.bind(this));
		this.view.minimizeButton.click(this.minimizeUnit.bind(this, 'mini'));
		this.view.unitHeader.mouseenter(this.unCloseUnit.bind(this));
		this.view.restoreButton.click(this.restoreUnit.bind(this));
		this.view.disableButton.click(this.disableUnit.bind(this));
	},

	cancelInitialMinimizing: function()
	{
		if (this.initialMinimizingTimer)
		{
			clearTimeout(this.initialMinimizingTimer);

			this.initialMinimizingTimer = null;
		}
	},

	isUnitMinimized: function()
	{
		var minimizedTimestamp = parseInt(localStorage.getItem('__sfGameHourModuleMinimized')) || 0;

		if (this.utils.isTimestampInRange(minimizedTimestamp, 86400000)) // 24hours
		{
			return true;
		}
	},

	isUnitSuperMinimized: function()
	{
		if (this.utils.isTimestampInRange(this.serverData.closedTimestamp, 86400000)) // 24hours
		{
			return true;
		}
	},


	positionToView: function()
	{
		var unitHeight = this.view.self.height();
		var unitFinalPosition = 0;

		if (this.isUnitSuperMinimized())
		{
			this.minimizedMode = 'supermini';
			unitFinalPosition = -(unitHeight-5);
		}
		else
		{
			if (this.isUnitMinimized())
			{
				this.minimizedMode = 'mini';
				this.view.self.addClass('minimized');
				unitFinalPosition = -(unitHeight-40);
			}
			else
			{
				this.initialMinimizingTimer = setTimeout(this.autoMinimizeUnit.bind(this), 30000);
			}
		}

		this.view.self.css({bottom:-unitHeight});
		this.view.self.animate({bottom:unitFinalPosition}, 200);
	},

	closeUnit: function()
	{
		this.utils.sendMessageToServerLayer.call(this, 'closeUnit', 'sf_close_gamehour');
		this.reportAction({action: 'gamehour hide'});
		this.hideUnit('supermini');
	},

	unCloseUnit: function()
	{
		if (this.minimizedMode == 'supermini')
		{
			this.utils.sendMessageToServerLayer.call(this, 'unCloseUnit', 'sf_close_gamehour');
			this.unHideUnit();
		}
	},

	minimizeUnit: function(mode, callback)
	{
		localStorage.setItem('__sfGameHourModuleMinimized', new Date().getTime());

		this.hideUnit(mode, callback);
		(mode == 'mini') && this.reportAction({action: 'gamehour minimized'});
	},

	autoMinimizeUnit: function()
	{
		this.hideUnit('mini');
	},

	restoreUnit: function()
	{
		localStorage.removeItem('__sfGameHourModuleMinimized');

		this.unHideUnit();
	},

	hideUnit: function(mode, callback) // modes: mini, supermini
	{
		var unitHeight = this.view.self.height();
		var visiblePartHeight;

		if (mode == 'mini')
		{
			visiblePartHeight = this.view.unitHeader.height();
			this.view.self.addClass('minimized');
		}
		else
		{
			visiblePartHeight = 5;
		}

		this.view.self.animate({bottom:-(unitHeight-visiblePartHeight)},
		{
			duration: 200,
			complete: callback || function(){}
		});

		this.minimizedMode = mode;
	},

	unHideUnit: function()
	{
		this.view.self.css({bottom: 0});
		this.view.self.removeClass('minimized');
		this.minimizedMode = false;

		this.reportAction({action: 'gamehour restored'});
	},

	showInfo: function()
	{
		similarproducts.info.ev(
		{
			position: 'fixed',
			left: 'auto',
			right: 15,
			bottom: 10
		}, 1, 1);

		similarproducts.info.pi("-9999" + similarproducts.b.xdMsgDelimiter + spsupport.p.initialSess);
	},

	renderInfo: function()
	{
		var info = similarproducts.info;

		info.jInfo = this.$('#' + info.infoId);

		if (info.jInfo.length == 0)
		{
			info.jInfo = this.$(info.ci(this.appDomain, similarproducts.b.dlsource, similarproducts.b.userid, similarproducts.b.CD_CTID, similarproducts.b.appVersion)).appendTo(document.body);
			info.jIfr = this.$('#' + info.infoId + '_CONTENT', info.jInfo);

			this.$('.closeButton', info.jInfo).click(function()
			{
				info.close();
			});
		}

	},

	disableUnit: function()
	{
		this.utils.sendMessageToServerLayer.call(this, 'disableUnit', 'sf_uninstall_gamehour');

		this.reportAction({action: 'gamehour disabled'});

		this.minimizeUnit('supermini', function()
		{
			this.view.self.remove();

		}.bind(this));
	},

	reportAction: function(data)
	{
		var pixel = new Image();
		var reportParamsString;

		data.userid = spsupport.p.userid;
		data.sessionid = this.serverData.sessionId;
		data.browser = spsupport.api.dtBr();
        data.page_url = window.location.href;
        data.merchantName = spsupport.p.siteDomain;
        data.dlsource = similarproducts.b.dlsource;
        data.country = similarproducts.b.userData.uc;

		reportParamsString = this.utils.compileQueryString(data);
	    reportParamsString += similarproducts.utilities.abTestUtil && similarproducts.utilities.abTestUtil.getDataString() || '';

		pixel.src = this.appDomain + 'trackSession.action?' + reportParamsString;
	}
};


similarproducts.gameHour.utils =
{
	extractDomainName: function(url)
	{
		var slicedUrl = url.toLowerCase().split('.');
        var length = slicedUrl.length;
        var tldRegex = /^(com|net|info|org|gov|co)$/; //TLD regex

        if (length > 2) // i.e. www.google.com.br, google.co.il, test.example.com
        {
            if (tldRegex.test(slicedUrl[length-2])) // Check second to last part if it passes the TLD regex.
            {
                slicedUrl.splice(0, length-3);
            }
            else
            {
                slicedUrl.splice(0, length-2);
            }
        }

        return slicedUrl.join('.');
	},

	compileQueryString: function(obj)
	{
		var result = [];

		for (key in obj)
		{
			if (obj.hasOwnProperty(key))
			{
				result.push(key + '=' + encodeURIComponent(obj[key]));
			}
		}

		return result.join('&');
	},

	concatObjects: function()
	{
		var result = {};
		var obj;

		for (var i=0, l=arguments.length; i<l; i++)
		{
			obj = arguments[i];

			for (var key in obj)
			{
				obj.hasOwnProperty(key) && (result[key] = obj[key]);
			}
		}

		return result;
	},

	isTimestampInRange: function(timestamp, range)
    {
        var now = new Date().getTime();

        return (timestamp + range > now);
    },

	serverMessagesRouter: function(event)
	{
		var data = event.originalEvent.data.split('__similarproductsGameHourNamespaceMarker')[1];

		data = data && JSON.parse(data) || null;

		if (data && typeof this[data.fn] === 'function')
		{
			this[data.fn](data.data);
		}
	},

	sendMessageToServerLayer: function(fn, data)
	{
		var targetWindow = this.serverLayerFrame.contentWindow || this.serverLayerFrame;
		var message =
        {
            fn: fn,
            data: data
        };

        targetWindow.postMessage('__similarproductsGameHourNamespaceMarker'+JSON.stringify(message), '*');
	}
};


similarproducts.gameHour.initialize();
