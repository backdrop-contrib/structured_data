/**
 * @file
 * Attaches comment behaviors to the node form.
 */

(function ($) {

  Backdrop.behaviors.structuredDataFieldsetSummaries = {

    attach: function (context) {
      var $context = $(context);

      // Provide the summary for the node type form.
      $context.find('fieldset.structured-data').backdropSetSummary(function() {
        var vals = [];

        // Schema.org type
        var type = $context.find("#edit-structured-data-schema option:selected").val();
        vals.push(Backdrop.t('Schema.org type: @type', {'@type': type}));

        return Backdrop.checkPlain(vals.join(', '));
      });
    }
  };

})(jQuery);

