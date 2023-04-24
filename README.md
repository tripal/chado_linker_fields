# Chado Linker Fields Documentation
**Tripal fields to display content linked to a different content type through linker tables**

This module provides fields for Tripal 7.x-3.10 or later to display linked content.
**Please be aware that this module will not be compatible with Tripal versions 7.x-3.9 or earlier.**



## Background

A number of content types have chado linker tables that define relationships between two
different content types. For example, in the core Tripal module there is a field named
`chado_linker__contact` that can be used, for example, to add contact information on a
feature, such as a gene. The correspondence information is stored in the chado table
`feature_contact`.
For example, this table might contain these records:
```
 feature_contact_id | feature_id | contact_id 
--------------------+------------+------------
                  1 |          1 |          3
                  2 |          2 |          3
```
And the linked contact could appear on a gene (feature) page as in this example

![chado_linker__contact example image](/docs/chado_linker__contact_example.png?raw=true "Example display of chado_linker__contact field")



## Fields Provided by This Module

This module provides linker fields for the following content types

| Linker Field Name | Controlled Vocabulary Term |
| --- | --- |
| chado_linker__analysis | [NCIT:C25391 (Analysis)]( https://www.ebi.ac.uk/ols/ontologies/ncit/terms?iri=http%3A%2F%2Fpurl.obolibrary.org%2Fobo%2FNCIT_C25391) |
| chado_linker__assay | [NCIT:C60819 (Assay)]( https://www.ebi.ac.uk/ols/ontologies/ncit/terms?iri=http%3A%2F%2Fpurl.obolibrary.org%2Fobo%2FNCIT_C60819) |
| chado_linker__biomaterial | [NCIT:C43376 (Biologically-Derived Material)]( https://www.ebi.ac.uk/ols/ontologies/ncit/terms?iri=http%3A%2F%2Fpurl.obolibrary.org%2Fobo%2FNCIT_C43376) |
| chado_linker__contact (**existing**) | local:contact |
| chado_linker__feature | [NCIT:C73619 (Feature)]( https://www.ebi.ac.uk/ols/ontologies/ncit/terms?iri=http%3A%2F%2Fpurl.obolibrary.org%2Fobo%2FNCIT_C73619) |
| chado_linker__featuremap | EDAM [data:1274 (map)](https://edamontology.github.io/edam-browser/#data_1274) |
| chado_linker__organism | [NCIT:C14250 (Organism)]( https://www.ebi.ac.uk/ols/ontologies/ncit/terms?iri=http%3A%2F%2Fpurl.obolibrary.org%2Fobo%2FNCIT_C14250) |
| chado_linker__project | [NCIT:C47885 (Project)](https://www.ebi.ac.uk/ols/ontologies/ncit/terms?iri=http%3A%2F%2Fpurl.obolibrary.org%2Fobo%2FNCIT_C47885) |
| chado_linker__stock | [NCIT:C48288 (Stock)]( https://www.ebi.ac.uk/ols/ontologies/ncit/terms?iri=http%3A%2F%2Fpurl.obolibrary.org%2Fobo%2FNCIT_C48288) |
| chado_linker__study | [NCIT:C63536 (Study)]( https://www.ebi.ac.uk/ols/ontologies/ncit/terms?iri=http%3A%2F%2Fpurl.obolibrary.org%2Fobo%2FNCIT_C63536) |

These fields can be used on any content type, however there must be a corresponding chado linker table, with a name based
on the two content types. For example, to link a stock to a project, the table can be named either `project_stock` or `stock_project`.
If Tripal does not provided a needed linker table, you can create a custom chado table yourself to store the linking information. See 
[the Tripal Documentation](https://tripal.readthedocs.io/en/latest/user_guide/custom_tables.html)
for more information on creating custom tables.



## How to add a field to a content type
These fields can be added to any content with an appropriate linker table.

On your site's admin menu, navigate to

Structure &rarr; Tripal content types

or navigate directly to

`/admin/structure/bio_data`.

On a content type click on `manage fields` and then click on `+ Check for new fields`
If a suitable linker table exists, a corresponding linker field will be added to the content type.
For example, on project content type you should see this result:

![project added fields example image](/docs/add_fields_to_project_example.png?raw=true "Example of adding fields to project content type")

You can then select the "MANAGE DISPLAY" tab, enable the fields if they are disabled, and
configure where you would like the new fields displayed.

![project manage display example image](/docs/configure_fields_on_project_example.png?raw=true "New fields on the Manage Display tab, ready to be configured")



## Configuration of Field Settings
On your site's admin menu, navigate to

Tripal &rarr; Data Storage &rarr; Chado &rarr; Field Settings

or navigate directly to

`/admin/tripal/storage/chado/field_settings`

The configuration form provides two settings:

![field settings form image](/docs/field_settings_form.png?raw=true "Appearance of the Field Settings administrative form")

## Maximum records to display
This setting is used to configure when a field converts to a summary view.
This is necessary when the number of records to display is too large for your site to handle.
For example, a Genome Assembly may be linked to all of the gene predictions in
that assembly, which will likely be tens of thousands of genes. Displaying this many records, even if a
pager is used, will likely overwhelm any Tripal site. In this case a summary view is returned.

Example of a summary view on an analysis (Gene Prediction) page:

![analysis_feature summary example image](/docs/analysis_feature_summary_example.png?raw=true "Example of a summary view on an analysis (Gene Prediction) page")

## Maximum field height
This setting is used to configure the maximum height of a single record displayed by a field.
For example, if linking an analysis to an organism, the analysis record may have an extensive
description, and if multiple analyses are linked, the resulting page that is displayed may be
unwieldy. When the content exceeds the specified height, a scrollbar will be provided.

Example of an analysis with scroll bar on a project page:

![maximum height example image](/docs/max_height_example.png?raw=true "Example of an analysis with scroll bar on a project page")



## Existing Linker Tables
Core Tripal provides the following linker tables compatible with the fields in this module.
Other modules may define additional linker tables.
```
analysis_organism
analysis_pub
analysisfeature
assay_biomaterial
assay_project
cell_line_feature
cell_line_library
cell_line_pub
feature_contact
featuremap_contact
featuremap_organism
featuremap_pub
library_contact
library_feature
library_pub
organism_pub
phylotree_pub
project_analysis
project_contact
project_feature
project_pub
project_stock
stock_feature
stock_featuremap
stock_library
stock_pub
stockcollection_stock
study_assay
```
